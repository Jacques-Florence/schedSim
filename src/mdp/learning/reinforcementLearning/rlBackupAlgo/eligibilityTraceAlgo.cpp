/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "eligibilityTraceAlgo.h"


#include <mdp/context.h>
#include <mdp/stateSpace.h>
#include <mdp/actionSpace.h>
#include <mdp/mdpConfiguration.h>


using namespace Mdp;

void EligibilityTraceAlgo::init()
{
	e = std::vector<std::vector<double>>(context->stateSpace->size(),
	                                     std::vector<double>(context->actionSpace->size(), 0.0));
	discountFactor = context->conf->getDoubleValue("mdp","discountFactor");
	lambda = context->conf->getDoubleValue("reinforcementLearning","lambda");
	stateSize = context->stateSpace->size();
	actionSize = context->actionSpace->size();
	initAlpha();
}

void EligibilityTraceAlgo::end()
{
}

void EligibilityTraceAlgo::updateState(state_t previousState, action_t previousAction, double reward)
{
	previousPreviousState = previousState;
	previousPreviousAction = previousAction;
	previousReward = reward;
	updateAlpha();
}

