/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlBackupAlgorithm.h"

#include <cassert>
#include <iostream>
#include <memory>

#include <utils/randomGenerator.h>

#include <mdp/context.h>
#include <mdp/mdpConfiguration.h>
#include <mdp/stateSpace.h>

#include <mdp/learning/reinforcementLearning/actionValuesFunction/actionValuesFunction.h>

using namespace Mdp;

RlBackupAlgorithm::RlBackupAlgorithm(std::shared_ptr<Context> c, ActionValuesFunction *av)
	: context(c)
	, actionValues(av)
	, bestQ(c->stateSpace->size())
	, bestAction(c->stateSpace->size())
	, needsUpdate(std::vector<bool>(c->stateSpace->size(), true))
{
}

void RlBackupAlgorithm::notifyUpdateNeeded()
{
	static size_t size = context->stateSpace->size();
	needsUpdate = std::vector<bool>(size, true);
}

double RlBackupAlgorithm::getMaxQ(state_t state)
{
	if (needsUpdate[state])
	{
		updateBestActionAndQ(state);
		needsUpdate[state] = false;
	}
	return bestQ[state];
}

void RlBackupAlgorithm::updateBestActionAndQ(state_t state)
{
	/*if ( state >= actionValues->size())
		std::cout << "state is "<<state<<" and actionValue size is "<<actionValues->size()<<" \n";
	assert(state < actionValues->size());*/
	double Q = actionValues->getValue(state, 0);
	double candidate;
	action_t action = 0;
	for (size_t i = 1; i < context->actionSpace->size(); i++)
	{
		candidate = actionValues->getValue(state, i);
		if (candidate >= Q)
		{
			const double eps = 0.0000001;//TODO: how to choose this value?
			if ((candidate < Q + eps) && (candidate > Q - eps) && context->randomGenerator->drawUniform(0.0, 2.0) > 1.0)
				continue;
			Q = candidate;
			action = i;
		}
	}
	bestQ[state] = Q;
	bestAction[state] = action;
}

std::pair<action_t, double> RlBackupAlgorithm::getBestActionAndQ(state_t state)
{
	updateIfNeeded(state);
	return std::pair<action_t, double>(bestAction[state], bestQ[state]);
}

void RlBackupAlgorithm::updateIfNeeded(state_t state)
{
	if (needsUpdate[state])
	{
		updateBestActionAndQ(state);
		needsUpdate[state] = false;
	}
}


action_t RlBackupAlgorithm::getBestAction(state_t state)
{
	updateIfNeeded(state);
	return bestAction[state];
}

void RlBackupAlgorithm::initAlpha()
{
	alpha = context->conf->getDoubleValue("reinforcementLearning","alpha");
	alphaDecaySpeed = context->conf->getDoubleValue("reinforcementLearning","alphaDecaySpeed");
	if (context->conf->getBoolValue("reinforcementLearning", "alphaHyperbolicDecay", false))
		hyperbolic = true;
	if (context->conf->getBoolValue("reinforcementLearning", "alphaStepwiseDecay", false))
	{
		stepwise = true;
		stepLength = context->conf->getUnsignedLongLongIntValue("reinforcementLearning", "alphaStepLength");
	}
	alpha0 = alpha;
}



void RlBackupAlgorithm::updateAlpha()
{
	if (hyperbolic)
	{
		alpha = alpha0/alphaCounter++;
	}
	if (stepwise)
	{
		stepwiseCounter++;
		if (stepwiseCounter == stepLength)
		{
			stepwiseCounter = 0;
			alpha *= alphaDecaySpeed;
		}
	}
}







