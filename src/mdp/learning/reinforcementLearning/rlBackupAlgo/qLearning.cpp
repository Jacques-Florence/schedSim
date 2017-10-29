/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "qLearning.h"

#include <cassert>
#include <iostream>

#include <mdp/context.h>
#include <mdp/mdpConfiguration.h>



using namespace Mdp;


QLearning::QLearning(std::shared_ptr<Context> c, TabularActionValues *actionValues)
	: RlBackupAlgorithm(c, actionValues)
	, tabularAv(actionValues)
{
}

void QLearning::init()
{
	assert(context != nullptr);
	assert(actionValues != nullptr);
	alpha = context->conf->getDoubleValue("reinforcementLearning","alpha");
	discountFactor = context->conf->getDoubleValue("mdp","discountFactor");
	alphaDecaySpeed = context->conf->getDoubleValue("reinforcementLearning", "alphaDecaySpeed");
	initAlpha();
}


void QLearning::end()
{
}



void QLearning::updateActionValues(state_t previousState, state_t newState, action_t previousAction, double reward)
{
	double Q = actionValues->getValue(previousState, previousAction);
	double newQ = Q + alpha*(reward - Q  + discountFactor*getMaxQ(newState));
	updateAlpha();
	tabularAv->updateValue(previousState, previousAction, newQ);
}











