/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "delayedQLearning.h"

using namespace Mdp;

void DelayedQLearning::updateActionValues(state_t previousState, state_t /*nextState*/, action_t previousAction, double reward)
{
	double delta = previousReward + discountFactor * getMaxQ(previousState);
	double av = actionValues->getValue(previousPreviousState, previousPreviousAction);
	delta -= av;
	tabularAv->updateValue(previousPreviousState, previousPreviousAction, av + alpha*delta);
	updateState(previousState, previousAction, reward);
}





























