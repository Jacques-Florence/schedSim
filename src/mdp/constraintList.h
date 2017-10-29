/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <vector>

namespace Mdp
{
class Rewards;

struct ConstraintList
{
	std::vector<Rewards*> equalityConstraints;
	std::vector<double> equalityValues;
	std::vector<Rewards*> inequalityConstraints;
	std::vector<double> inequalityValues;
};


}
#endif
