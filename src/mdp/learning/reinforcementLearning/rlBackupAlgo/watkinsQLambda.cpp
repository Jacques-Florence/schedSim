/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "watkinsQLambda.h"

#include <cassert>

#include <mdp/context.h>
#include <utils/randomGenerator.h>

using namespace Mdp;

void WatkinsQLambda::updateActionValues(state_t previousState, state_t /*nextState*/, action_t previousAction, double reward)
{
	std::pair<double, action_t> pair = watkinsBestQ(previousState, previousAction);
	double newQ = pair.first;
	action_t astar = pair.second;
	double delta = previousReward + discountFactor * newQ;
	delta -= actionValues->getValue(previousPreviousState, previousPreviousAction);
	

	e[previousPreviousState][previousPreviousAction] += 1.0;
	for (size_t i = 0; i < stateSize; i++)
	{
		for (size_t j = 0; j < actionSize; j++)
		{
			double av = actionValues->getValue(i, j);
			double newValue = av + alpha*delta*e[i][j];
			tabularAv->updateValue(i, j, newValue);
			if (astar == previousAction)
			{
				e[i][j] *= discountFactor*lambda;
			}
			else
			{
				e[i][j] = 0.0;
			}
		}
	}
	updateState(previousState, previousAction, reward);
}



std::pair<double, action_t> WatkinsQLambda::watkinsBestQ(state_t state, action_t nextAction)
{
	double Q = actionValues->getValue(state, 0);
	double candidate;
	action_t action = 0;
	for (size_t i = 1; i < actionSize; i++)
	{
		candidate = actionValues->getValue(state, i);
		static const double lowerMargin = 0.99999;//TODO: how to choose those
		static const double upperMargin = 1.00001;
		if ((candidate > Q*lowerMargin) && (candidate < Q*upperMargin))
		{
			if (action == nextAction)
			{
				continue;
			}
			else if (i == nextAction)
			{
				Q = candidate;	
				action = i;
				continue;
			}
			else
			{
				if (context->randomGenerator->drawUniform(0.0, 2.0) > 1.0)
					continue;
				Q = candidate;
				action = i;
			}
		}
		else if (candidate > Q)
		{	
			Q = candidate;
			action = i;
		}
	}
	return std::pair<double, action_t>(Q, action);
}













