/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "gibbsActionSelection.h"

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <limits>

using namespace Mdp;

GibbsActionSelection::GibbsActionSelection(double t, double tDecaySpeed, double tStepSize)
	: temperature(t)
	, tempDecaySpeed(tDecaySpeed)
	, tempStepSize(tStepSize)
{
}

std::vector<double> GibbsActionSelection::generatePolicy(const std::vector<double>& actionValues, action_t /*bestAction*/)
{
	std::vector<double> policy = std::vector<double>(actionValues.size());
	double sum = 0.0;
	size_t maxCandidate = 0;
	double maxCandidateValue = -std::numeric_limits<double>::infinity();
	for (size_t i = 0; i < policy.size(); i++)
	{
		double var = actionValues[i]/temperature;
		
		policy[i] = exp(var);
		//std::cerr << "policy["<<i<<"] is "<<policy[i]<<" = exp("<<var<<")\n";
		sum += policy[i];
		if (var > maxCandidateValue)
		{
			maxCandidateValue = var;
			maxCandidate = i;
		}
	}
	//std::cerr << "sum is "<< sum <<"\n";
	for (size_t i = 0; i < policy.size(); i++)
	{
		if (sum <= 0.0 && sum >= 0.0) /*FIXME maybe we can compare the value of the max to the value of the secondmax*/
			policy[i] = (i == maxCandidate) ? 1.0 : 0.0;
		else
			policy[i] /= sum;
		//std::cerr << "policy[" << i << "] is "<< policy[i] <<"\n";
	}
	updateTemperature();
	return policy;
}

void GibbsActionSelection::updateTemperature()
{
	static long long unsigned int counter = 0;
	if (counter ++>= tempStepSize)
	{
		temperature *= tempDecaySpeed;
		counter = 0;
	}
}



