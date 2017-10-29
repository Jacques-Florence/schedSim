/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPREWARDS_H
#define MDPREWARDS_H

#include <ostream>
#include <vector>

#include "action_impl.h"
#include "state.h"

namespace Mdp
{


class Rewards
{
public:
	Rewards(size_t nbOfStates, size_t nbOfActions);	
	double getReward(state_t, action_t);
	void setReward(state_t state, action_t action, double reward);
	void print(std::ostream& stream);
	size_t getNbOfStates(){return nbOfStates;};
	size_t getNbOfActions(){return nbOfActions;};
private:
	size_t nbOfStates;
	size_t nbOfActions;
	std::vector< std::vector<double> > rewards;
};

}
#endif
