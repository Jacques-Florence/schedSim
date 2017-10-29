/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "neuroQ.h"

#include <stdexcept>

#include <mdp/context.h>
#include <mdp/stateSpace.h>
#include <mdp/actionSpace.h>
#include <mdp/mdpConfiguration.h>

using namespace Mdp;


void NeuroQ::init()
{
	alpha0 = context->conf->getDoubleValue("reinforcementLearning", "alpha");
	alpha = alpha0;
	targetNetwork = new NeuralNetwork(context, approximatedAv->getNbInputs(),
	approximatedAv->getNbHidden(), approximatedAv->getNbOutputs());
	targetUpdateInterval = context->conf->getIntValue("reinforcementLearning", "targetUpdateInterval");
}

void NeuroQ::end()
{
}

void NeuroQ::updateActionValues(state_t previousState, state_t nextState, action_t previousAction, double reward)
{
	//double Q = actionValues->getValues(previousState);
#if 0
	if (reward > 0)
	{
		reward = 1.0;
	}
	else if (reward < 0)
	{
		reward = -1.0;
	}
	else
	{
		reward = 0.0;
	}
#endif
	approximatedAv->setAlpha(alpha);
	updateAlpha();
	approximatedAv->learnExample(generateInputVector(previousState)
	                           , generateTargetOutput(reward, previousState, nextState, previousAction));
}

std::vector<double> NeuroQ::generateTargetOutput(double reward, state_t previousState, state_t nextState, action_t previousAction)
{
	updateTargetNetwork();
	double target = (reward + discountFactor*getTargetMaxQ(nextState));
	std::vector<double> actionValuesVector = actionValues->getValues(previousState);
	actionValuesVector[previousAction] = target;
	return actionValuesVector;
}

void NeuroQ::updateTargetNetwork()
{
	static int counter = 0;
	if (++counter == targetUpdateInterval)
	{
		counter = 0;
		std::vector<double> weights = approximatedAv->getParameters();
		targetNetwork->setWeights(weights);
	}
}

std::vector<double> NeuroQ::generateInputVector(state_t previousState)
{
	std::vector<double> stateVector = getStateVector(previousState);
	std::vector<double> inputVector = stateVector;

	//preprocessing
	static std::vector<size_t> dimensionSizes = context->stateSpace->getDimensionSizes();
	static size_t dimensions = getNbOfStateDimensions();
	for (size_t i = 0; i < dimensions; i++)
	{
#if 0
		//rescale to be between -0.5 and +0.5
		if (dimensionSizes[i] >= 2)
		{
			inputVector[i] /= (dimensionSizes[i] - 1.0);
		}
		else
		{
			inputVector[i] = 0.0;
		}
		inputVector[i] -= 0.5;
#else
		inputVector[i] -= 1.0;
#endif
	}
	return inputVector;
}


size_t NeuroQ::getNbOfStateDimensions()
{
	return context->stateSpace->getNbOfDimensions();
}

std::vector<double> NeuroQ::getStateVector(state_t state)
{
	std::vector<size_t> *vect = context->stateSpace->factorize(state);
	std::vector<double> retval(context->stateSpace->getNbOfDimensions());
	for (size_t i = 0; i < context->stateSpace->getNbOfDimensions(); i++)
	{
		retval[i] = (*vect)[i];
	}
	return retval;
}



double NeuroQ::getMaxQ(state_t state)
{
	std::vector<double> actionValuesVector = approximatedAv->getValues(state);
	double candidate = actionValuesVector[0];
	for (size_t i = 1; i < actionValuesVector.size(); i++)
	{
		if (actionValuesVector[i] > candidate)
			candidate = actionValuesVector[i];
	}
	return candidate;
}

double NeuroQ::getTargetMaxQ(state_t state)
{
	std::vector<double> actionValuesVector = targetNetwork->getValues(state);
	double candidate = actionValuesVector[0];
	for (size_t i = 1; i < actionValuesVector.size(); i++)
	{
		if (actionValuesVector[i] > candidate)
			candidate = actionValuesVector[i];
	}
	return candidate;
}

std::pair<action_t, double> NeuroQ::getBestActionAndQ(state_t state)
{
	std::pair<action_t, double> p;
	p.first = getBestAction(state);
	p.second = getMaxQ(state);
	return p;
}

action_t NeuroQ::getBestAction(state_t state)
{
	action_t best = 0;
	std::vector<double> avect = approximatedAv->getValues(state);
	double bestValue = avect[0];
	for (size_t i = 1; i < avect.size(); i++)
	{
		if (avect[i] > bestValue)
		{
			bestValue = avect[i];
			best = i;
		}
	}
	return best;
}

void NeuroQ::notifyUpdateNeeded()
{
}






