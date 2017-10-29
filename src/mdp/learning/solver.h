/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SOLVER_H
#define SOLVER_H

namespace Mdp
{
class Policy;
class Rewards;
class ConstraintList;
class TransitionMatrix;
struct Horizon;

class Solver
{
public:
	virtual ~Solver(){};
	virtual void solve(Policy *policy, Rewards *rewards, ConstraintList *constraintList,
		TransitionMatrix *matrix, Horizon *horizon)=0;
};

}

#endif
