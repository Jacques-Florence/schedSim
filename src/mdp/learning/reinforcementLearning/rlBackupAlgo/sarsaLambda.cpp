/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "sarsaLambda.h"

#include <cassert>
#include <iostream>

using namespace Mdp;


void SarsaLambda::updateActionValues(state_t previousState, state_t /*nextState*/, action_t previousAction, double reward)
{
	double delta = previousReward + discountFactor * actionValues->getValue(previousState, previousAction);
	delta -= actionValues->getValue(previousPreviousState, previousPreviousAction);
	
	e[previousPreviousState][previousPreviousAction] += 1.0;
	for (size_t i = 0; i < stateSize; i++)
	{
		for (size_t j = 0; j < actionSize; j++)
		{
			double av = actionValues->getValue(i, j);
			double newValue = av + alpha*delta*e[i][j];
			tabularAv->updateValue(i, j, newValue);
			e[i][j] *= discountFactor*lambda;
		}
	}
	updateState(previousState, previousAction, reward);
}







