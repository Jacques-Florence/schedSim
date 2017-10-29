/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "reinforcedLearning.h"

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <utils/randomGenerator.h>
#include <utils/stringUtils.h>

#include <mdp/mdpConfiguration.h>
#include <mdp/context.h>
#include <mdp/actionSpace.h>
#include <mdp/policy.h>
#include <mdp/stateSpace.h>

#include "rlBackupAlgo/qLearning.h"
#include "rlBackupAlgo/sarsaLambda.h"
#include "rlBackupAlgo/delayedQLearning.h"
#include "rlBackupAlgo/naiveQLambda.h"
#include "rlBackupAlgo/watkinsQLambda.h"
#include "rlBackupAlgo/neuroQ.h"

#include "actionSelection/actionSelectionStrategy.h"
#include "actionSelection/epsilonGreedy.h"
#include "actionSelection/gibbsActionSelection.h"

#include "actionValuesFunction/tabularActionValues.h"
#include "actionValuesFunction/neuralNetwork.h"

using namespace Mdp;


ReinforcedLearning::ReinforcedLearning(std::shared_ptr<Context> c)
	: LearningStrategy(c)
	, S(c->stateSpace->size())
	, A(c->actionSpace->size())
	, actionValuesRecord(ActionValuesRecord(c->conf, S, A))
	, rewardRecord(c->conf, "rewardRecord")
{
	assert(context != nullptr);
	assert(context->conf != nullptr);
}

ReinforcedLearning::~ReinforcedLearning()
{
	if (backupAlgo != nullptr)
		delete backupAlgo;
}

/*TODO: what to do with initializeModel vs constructor?
 * initializeModel is a public function. Why? Where is it called?*/
void ReinforcedLearning::initializeModel()
{
	previousState = context->stateSpace->getState();
	std::cerr << "initial state is: " << previousState <<"\n";
	initializePolicy();
	assert(context != nullptr);
	assert(context->conf != nullptr);
	backupAlgo = getBackupAlgorithm();
	backupAlgo->init();
	actionValuesRecord.init();
	/*FIXME: REDUNDANT*/
	initializePolicy();
	initializeActionSelectionStrategy();
	printStateSpace();
}

void ReinforcedLearning::printStateSpace()
{
#ifdef PRINT
	size_t S = context->stateSpace->size();
	for (size_t s = 0; s < S; s++)
	{
		std::vector<size_t> *vect = context->stateSpace->factorize(s);
		for (size_t i = 0; i < vect->size(); i++)
		{
			std::cerr << (*vect)[i] << " ";
		}
		std::cerr << "\n";
	}
#endif
}

void ReinforcedLearning::initializeActionSelectionStrategy()
{
	std::string str = context->conf->getStringValue("reinforcementLearning", "actionSelectionStrategy");
	if (!str.compare("epsilonGreedy"))
	{
		double epsilon = context->conf->getRlEpsilonFromFile();
		double epsilonDecaySpeed = context->conf->getDoubleValue(
			"reinforcementLearning", "epsilonDecaySpeed");
		long long unsigned int epsilonTimeout = context->conf->getUnsignedLongLongIntValue(
			"reinforcementLearning", "epsilonTimeOut");
		actionSelectionStrategy = new EpsilonGreedy(epsilon, epsilonDecaySpeed, epsilonTimeout);
	}
	else if (!str.compare("greedy"))
	{
		actionSelectionStrategy = new EpsilonGreedy(0.0, 0.0, 0);
	}
	else if (!str.compare("Gibbs"))
	{
		double temperature = context->conf->getDoubleValue("reinforcementLearning", "GibbsTemperature");
		double tempDecaySpeed = context->conf->getDoubleValue("reinforcementLearning", "GibbsTempDecaySpeed");
		double tempStepSize = context->conf->getDoubleValue("reinforcementLearning", "GibbsTempStepSize");
		actionSelectionStrategy = new GibbsActionSelection(temperature, tempDecaySpeed, tempStepSize);
	}
	else
	{
		throw std::invalid_argument("invalid value for actionSelectionStrategy");
	}
}


void ReinforcedLearning::initializePolicy()
{
	std::string initStr = context->conf->getStringValue("reinforcementLearning", "initialPolicy");
	if (!initStr.compare("uniform"))
	{
		context->policy->initializeUniformly();
	}
	else if (!initStr.compare("fromFile"))
	{
		/*TODO: path is hardcoded*/
		context->policy->initializeFromFile("configuration/initialPolicy");
	}
	else
	{
		throw std::invalid_argument("initial policy not defined");
	}
}

RlBackupAlgorithm *ReinforcedLearning::getBackupAlgorithm()
{
	std::string str = context->conf->getStringValue("reinforcementLearning", "algo");
	if (!str.compare(QLearning::configKey))
	{
		actionValues = new TabularActionValues(context);
		return new QLearning(context, dynamic_cast<TabularActionValues*>(actionValues));
	}
	if (!str.compare(SarsaLambda::configKey))
	{
		actionValues = new TabularActionValues(context);
		return new SarsaLambda(context, dynamic_cast<TabularActionValues*>(actionValues));
	}
	if (!str.compare(DelayedQLearning::configKey))
	{
		actionValues = new TabularActionValues(context);
		return new DelayedQLearning(context, dynamic_cast<TabularActionValues*>(actionValues));
	}
	if (!str.compare(WatkinsQLambda::configKey))
	{
		actionValues = new TabularActionValues(context);
		return new WatkinsQLambda(context, dynamic_cast<TabularActionValues*>(actionValues));
	}
	if (!str.compare(NaiveQLambda::configKey))
	{
		actionValues = new TabularActionValues(context);
		return new NaiveQLambda(context, dynamic_cast<TabularActionValues*>(actionValues));
	}
	if (!str.compare(NeuroQ::configKey))
	{
		int hiddenUnits = context->conf->getIntValue("reinforcementLearning", "hiddenUnits");
		actionValues = new NeuralNetwork(context, context->stateSpace->getNbOfDimensions(), hiddenUnits, context->actionSpace->size());
		return new NeuroQ(context, dynamic_cast<NeuralNetwork*>(actionValues));
	}
	throw std::runtime_error("Reinforcement Learning algorithm lookup failed");
}


void ReinforcedLearning::updateModel()
{
	/*We use Q-learning*/
	previousAction = context->actionSpace->getLastAction();
	state_t newState = context->stateSpace->getState();
	double reward = context->stateSpace->getReward();
	if (reward == -HUGE_VAL)
		reward = -1.0e100;

	static double discountFactor = context->conf->getDoubleValue("mdp", "discountFactor");
	updateLongTermReward(reward, discountFactor);

	//updateActualDiscountedReward(reward);
	backupAlgo->notifyUpdateNeeded();
	backupAlgo->updateActionValues(previousState, newState, previousAction, reward);
	actionValuesRecord.recordActionValues(actionValues, previousState, previousAction);

	updatePolicy(previousState);
	previousState = newState;
}

void ReinforcedLearning::updateLongTermReward(double reward, double discountFactor)
{
	longTermReward *= discountFactor;
	longTermReward += reward;
}

void ReinforcedLearning::updateActualDiscountedReward(double reward)
{
	static long long int counter = 0;
	actualDiscountedReward *= discountFactor;
	actualDiscountedReward += reward;

	rewardRecord.add(counter++, actualDiscountedReward);
}

void ReinforcedLearning::updatePolicy(state_t state)
{
	static const bool updatePolicy = context->conf->getBoolValue("reinforcementLearning", "updatePolicy", true);
	if (!updatePolicy)
	{
		return;
	}
	epsilonGreedyPolicyUpdate(state); //FIXME: remove epsilongreedy from the name
}

void ReinforcedLearning::epsilonGreedyPolicyUpdate(state_t state)
{
	action_t bestAction = getBestAction(state);
	std::vector<double> av = actionValues->getValues(state);
	//bestAction = getBestActionFromInitialPolicy(state);
	std::vector<double> policy = actionSelectionStrategy->generatePolicy(av, bestAction);
	context->policy->update(state, policy);
}

action_t ReinforcedLearning::getBestActionFromInitialPolicy(state_t s)
{
	size_t S = context->stateSpace->size();
	size_t A = context->actionSpace->size();
	static std::vector<std::vector<double>> init(S, std::vector<double>(A));
	static bool valid = false;
	static std::vector<action_t> bestAction(S);
	if (!valid)
	{
		valid = true;
		std::string filename = "configuration/initialPolicy";
		std::fstream stream;
		stream.open(filename);
		if (!stream.is_open())
			throw std::runtime_error("cannot open file");
		std::string line;
		std::vector<std::vector<double>> pol;
		size_t a = 0;
		while(std::getline(stream, line))
		{
			std::vector<std::string> elements = Utils::StringUtils::split(line, ' ');
			std::vector<double> row;
			/*TODO: this can be rewritten more elegantly*/
			for (size_t i = 0; i < elements.size(); i++)
			{
				row.push_back(std::stod(elements[i]));
			}
			init[a++] = row;
		}
		double bestValue;
		for (size_t s = 0; s < S; s++)
		{
			bestAction[s] = 0;
			bestValue = init[s][0];
			for (size_t a = 1; a < A; a++)
			{
				if (init[s][a] > bestValue)
				{
					bestValue = init[s][a];
					bestAction[s] = a;
				}
			}
		}
	}
	
	return bestAction[s];
}

action_t ReinforcedLearning::getBestAction(state_t state)
{
	return backupAlgo->getBestAction(state);
}


void ReinforcedLearning::end()
{
	actionValuesRecord.end();
#ifdef PRINT
	/*Action values are Q-learning's equivalent to mdp policy table*/
	printActionValuesToFile("./");
#endif
	rewardRecord.printToFile("reports");
#ifdef PRINT
	std::cerr << "the long-term reward is " << longTermReward <<"\n";
#endif
}


void ReinforcedLearning::printActionValuesToFile(std::string folder)
{
	std::ofstream file;
	std::ofstream normalized;
	file.open(folder + "/rlfile.txt", std::ios_base::app);
	normalized.open(folder + "/rlfilenormalized.txt", std::ios_base::app);
	for (unsigned int i = 0; i < S; i++)
	{
		bool allEqual = true;
		unsigned int maxIndex = 0;
		double maxValue = actionValues->getValue(i, 0);
		for (size_t j = 1; j < A; j++)
		{
			if (actionValues->getValue(i, j) > maxValue)
			{
				maxValue = actionValues->getValue(i, j);
				maxIndex = j;
			}
			double eps = 0.0000001; //TODO: what value should this be? Maybe make it relative to the abs value of actionValues[i][j]
			if (actionValues->getValue(i, j) < actionValues->getValue(i, j-1) - eps
				|| actionValues->getValue(i, j) > actionValues->getValue(i, j-1) + eps)
				allEqual = false;
		}
		for (unsigned int j = 0; j < A; j++)
		{
			file << actionValues->getValue(i, j)<<" ";
			normalized << ((allEqual == true) ? 1 : ((j == maxIndex) ? 1 : 0) ) <<" ";
		}
		file << "\n";
		normalized << "\n";
	}
	file.close();
	normalized.close();
}































