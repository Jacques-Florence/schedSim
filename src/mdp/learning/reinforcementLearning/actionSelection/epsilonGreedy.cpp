/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "epsilonGreedy.h"

#include <iostream>

using namespace Mdp;

EpsilonGreedy::EpsilonGreedy(double e, double eDecaySpeed, long long unsigned int eTimeout)
	: epsilon(e)
	, epsilonDecaySpeed(eDecaySpeed)
	, epsilonTimeout(eTimeout)
{
}


std::vector<double> EpsilonGreedy::generatePolicy(const std::vector<double>& actionValues, action_t bestAction)
{
	static size_t nbActions = actionValues.size();
	static std::vector<double> policy(nbActions);
	static const size_t nbActionsMinusOne = nbActions - 1;
	const double bestActionProba = 1.0 - epsilon;
	const double otherActionProba = epsilon / (double) nbActionsMinusOne;
	for (action_t i = 0; i < nbActions; i++)
	{
		policy[i] = ((i == bestAction) ? bestActionProba : otherActionProba);
	}
	updateEpsilon();
	return policy;
}

void EpsilonGreedy::updateEpsilon()
{
	static long long unsigned int counter = 0;
	epsilon *= epsilonDecaySpeed;
	if (epsilonTimeout && (counter ++> epsilonTimeout))//if epsilonTimeOut is set to 0, there's no timeout
	{
		epsilon = 0.0;
		epsilonTimeout = 0; //this improves performance somewhat
	}
}


