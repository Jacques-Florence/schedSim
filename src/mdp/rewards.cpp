/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rewards.h"

#include <ostream>

using namespace Mdp;

Rewards::Rewards(size_t S, size_t A) :
	nbOfStates(S),
	nbOfActions(A),
	rewards(std::vector<std::vector<double>>(S, std::vector<double>(A, 0.0)))
{
}

double Rewards::getReward(state_t state, action_t action)
{
	return rewards[state][action];
}

void Rewards::setReward(state_t state, action_t action, double reward)
{
	rewards[state][action] = reward;
}


void Rewards::print(std::ostream& stream)
{
	stream << "Printing rewards/costs\n";
	for (state_t i = 0; i < nbOfStates; i++)
	{
		for (action_t j = 0; j < nbOfActions; j++)
		{
			stream << rewards[i][j] << "  ";
		}
		stream << "\n";
	}
}




