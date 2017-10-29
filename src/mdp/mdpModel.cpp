/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "mdpModel.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include <utils/randomGenerator.h>

#include "action.h"
#include "action_impl.h"
#include "actionSpace.h"
#include "constraintList.h"
#include "context.h"
#include "horizon.h"
#include "learning/learningStrategy.h"
#include "mdpConfiguration.h"
#include "policy.h"
#include "rewards.h"
#include "stateSpace.h"
#include "transitionMatrix.h"

using namespace Mdp;


MdpModel::MdpModel(std::shared_ptr<StateSpace> stateSpace,
                   std::shared_ptr<ActionSpace> actionSpace,
                   std::shared_ptr<MdpConfiguration> conf)
{
	constructContext(stateSpace, actionSpace, conf);
	setLearningStrategy();
}

void MdpModel::setLearningStrategy()
{
	assert(context);
	learningStrategy = context->conf->getLearningStrategyFromFile(context);
}

void MdpModel::constructContext(std::shared_ptr<StateSpace> stateSpace,
                                std::shared_ptr<ActionSpace> actionSpace,
                                std::shared_ptr<MdpConfiguration> conf)
{
	context = std::make_shared<Context>();
	context->stateSpace = stateSpace;
	context->actionSpace = actionSpace;
	size_t s = context->stateSpace->size();
	size_t a = context->actionSpace->size();
	context->matrix = std::make_shared<TransitionMatrix>(s, a);
	context->rewards = std::make_shared<Rewards>(s, a);
	context->constraintList = std::make_shared<ConstraintList>();
	context->randomGenerator = std::make_shared<Utils::RandomGenerator>();
	context->randomGenerator->seed(conf->getIntValue("mdp","seed"));
	context->policy = std::make_shared<Policy>(s, a, context->randomGenerator);
	context->conf = conf;
	context->horizon = std::shared_ptr<Horizon>(context->conf->getHorizonFromFile());
	context->horizon->initialStateDistribution = std::vector<double>(s, 1.0/s);
}

MdpModel::~MdpModel()
{
}

void MdpModel::init()
{
	context->stateSpace->updateCurrentState();
	learningStrategy->initializeModel();
	recordHistory = context->conf->getBoolValue("mdp", "recordHistory", false);
}

void MdpModel::end()
{
	learningStrategy->end();
}

Action *MdpModel::selectActionWithoutUpdate()
{
	return selectAction(false);
}

Action *MdpModel::selectAction(bool updateModel)
{
	context->stateSpace->updateCurrentState();
	if (updateModel)
		learningStrategy->updateModel();
	state_t state = context->stateSpace->getState();
	action_t action = context->policy->getAction(state);
	context->actionSpace->updateLastAction(action);
	if (recordHistory)
		record(state, action, context->stateSpace->getReward());
	return context->actionSpace->getAction(action);
}


void MdpModel::printReportsToFile(std::string folder)
{
	std::ofstream file;
	file.open(folder + "/transitionMatrix.txt", std::ios_base::app);
	context->matrix->print(file);
	file.close();

	std::ofstream policyFile;
	policyFile.open(folder + "/policy.txt", std::ios_base::app);
	context->policy->print(policyFile);
	policyFile.close();

	std::ofstream summaryFile;
	summaryFile.open(folder + "/mdpSummary.txt", std::ios_base::app);
	printSummary(summaryFile);
	summaryFile.close();
}


void MdpModel::printPolicy(std::ostream& stream)
{
	context->policy->print(stream);	
}



void MdpModel::record(state_t state, action_t action, double reward)
{
	if (recordHistory)
	{
		stateHistory.push_back(state);
		actionHistory.push_back(action);
		rewardHistory.push_back(reward);
	}
}



void MdpModel::printSummary(std::ostream& stream)
{
	stream << "Summary of MDP\n";
	stream << "state statistics:\n";
	stream << "distribution of states visited:\n";
	std::vector<int> stateCount(context->stateSpace->size());
	for (size_t i = 0; i < stateHistory.size(); i++)
	{
		stateCount[stateHistory[i]]++;
	}
	int sum = 0;
	for (size_t i = 0; i < stateCount.size(); i++)
	{
		sum += stateCount[i];
	}
	for (size_t i = 0; i < stateCount.size(); i++)
	{
		stream << i << ": " << ((double)stateCount[i]) / ((double)sum) << "\n";
	}
}

void MdpModel::setConstraintList(std::shared_ptr<ConstraintList> list)
{
	context->constraintList = list;
}

void MdpModel::setRewards(std::shared_ptr<Rewards> rewards)
{
	context->rewards = rewards;
}




