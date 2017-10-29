/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "naiveQLambda.h"

#include <mdp/context.h>

using namespace Mdp;

void NaiveQLambda::updateActionValues(state_t previousState, state_t /*nextState*/, action_t previousAction, double reward)
{
	double delta = previousReward + discountFactor * getMaxQ(previousState);
	double av = actionValues->getValue(previousPreviousState, previousPreviousAction);
	delta -= av;
	
	e[previousPreviousState][previousPreviousAction] += 1.0;
	for (size_t i = 0; i < stateSize; i++)
	{
		for (size_t j = 0; j < actionSize; j++)
		{
			double update = alpha*delta*e[i][j];
			double newValue = actionValues->getValue(i, j) + update;
			tabularAv->updateValue(i, j, newValue);
			e[i][j] *= discountFactor*lambda;
		}
	}
	updateState(previousState, previousAction, reward);
}




