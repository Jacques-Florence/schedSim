/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "learning/linearProgramming.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "constraintList.h"
#include "horizon.h"
#include "mdpConfiguration.h"
#include "policy.h"
#include "rewards.h"
#include "transitionMatrix.h"


using namespace Mdp;

Rewards *generateRewards();
TransitionMatrix *generateTransitionMatrix();
std::vector<Rewards*> generateEqualityConstraints();
std::vector<double> generateEqualityValues();
std::vector<Rewards*> generateInequalityConstraints();
std::vector<double> generateInequalityValues();
Horizon *generateHorizon();

const size_t S = 9;
const size_t A = 3;

const double C1 = 1.0;
const double C2 = 200.0;
const double f1 = 5.0;
const double f2 = 8.0;
const double co = 0.0;
const double cl = C1*f1*f1 + C2;
const double ch = C1*f2*f2 + C2;
const double f3 = 2.0;
const double ctr = 0.0;

const double pol = 0.5;
const double plo = 0.5;
const double poh = 0.5;
const double pho = 0.5;
const double phl = 0.5;
const double plh = 0.5;








int main()
{
	Policy *policy = new Policy(S, A, nullptr);
	Rewards *rewards = generateRewards();
	ConstraintList *constraintList = new ConstraintList;
	constraintList->equalityConstraints = generateEqualityConstraints();
	constraintList->equalityValues = generateEqualityValues();
	constraintList->inequalityConstraints = generateInequalityConstraints();
	constraintList->inequalityValues = generateInequalityValues();
	TransitionMatrix *matrix = generateTransitionMatrix();
	Utils::Configuration *conf = new Utils::Configuration("configuration.conf");
	Horizon *horizon = generateHorizon();

	LinearProgramming solver(conf);
	solver.solve(policy, rewards, constraintList, matrix, horizon);
	
	policy->print(std::cout);
	//matrix->print(std::cout);
	
	return 0;
}



Horizon *generateHorizon()
{
	Horizon *h = new Horizon;
	h->discountFactor = 1.0;
	h->finiteHorizon = false;
	std::vector<double> vect(S, 1.0/S);
	h->initialStateDistribution = vect;
	return h;
}



Rewards *generateRewards()
{
	Rewards *rewards = new Rewards(S, A);

	rewards->setReward(0, 0, -co - 0.0001);
	rewards->setReward(0, 1, -co);
	rewards->setReward(0, 2, -co);

	rewards->setReward(1, 0, -ctr);
	rewards->setReward(1, 1, -ctr);
	rewards->setReward(1, 2, -ctr);

	rewards->setReward(2, 0, -ctr);
	rewards->setReward(2, 1, -ctr);
	rewards->setReward(2, 2, -ctr);

	rewards->setReward(3, 0, -cl );
	rewards->setReward(3, 1, -cl );
	rewards->setReward(3, 2, -cl );

	rewards->setReward(4, 0, -ctr);
	rewards->setReward(4, 1, -ctr);
	rewards->setReward(4, 2, -ctr);

	rewards->setReward(5, 0, -ctr);
	rewards->setReward(5, 1, -ctr);
	rewards->setReward(5, 2, -ctr);

	rewards->setReward(6, 0, -ch );
	rewards->setReward(6, 1, -ch );
	rewards->setReward(6, 2, -ch );

	rewards->setReward(7, 0, -ctr);
	rewards->setReward(7, 1, -ctr);
	rewards->setReward(7, 2, -ctr);

	rewards->setReward(8, 0, -ctr);
	rewards->setReward(8, 1, -ctr);
	rewards->setReward(8, 2, -ctr);

	return rewards;
}








TransitionMatrix *generateTransitionMatrix()
{
	TransitionMatrix *matrix = new TransitionMatrix(S, A);

	for (state_t i = 0; i < S; i++)
	{
		for (state_t j = 0; j < S; j++)
		{
			for (action_t k = 0; k < A; k++)
			{
				matrix->set(i, j, k, 0.0);
			}
		}
	}
	matrix->set(0, 0, 0, 1.0);
	matrix->set(0, 1, 1, 1.0);
	matrix->set(0, 4, 2, 1.0);
	matrix->set(1, 1, 0, pol);
	matrix->set(1, 3, 0, 1.0-pol);
	matrix->set(1, 1, 1, pol);
	matrix->set(1, 3, 1, 1.0-pol);
	matrix->set(1, 1, 2, pol);
	matrix->set(1, 3, 2, 1.0-pol);
	matrix->set(2, 0, 0, 1.0-plo);
	matrix->set(2, 2, 0, plo);
	matrix->set(2, 0, 1, 1.0-plo);
	matrix->set(2, 2, 1, plo);
	matrix->set(2, 0, 2, 1.0-plo);
	matrix->set(2, 2, 2, plo);
	matrix->set(3, 2, 0, 1.0);
	matrix->set(3, 3, 1, 1.0);
	matrix->set(3, 8, 2, 1.0);
	matrix->set(4, 4, 0, poh);
	matrix->set(4, 6, 0, 1.0-poh);
	matrix->set(4, 4, 1, poh);
	matrix->set(4, 6, 1, 1.0-poh);
	matrix->set(4, 4, 2, poh);
	matrix->set(4, 6, 2, 1.0-poh);
	matrix->set(5, 0, 0, 1.0-pho);
	matrix->set(5, 5, 0, pho);
	matrix->set(5, 0, 1, 1.0-pho);
	matrix->set(5, 5, 1, pho);
	matrix->set(5, 0, 2, 1.0-pho);
	matrix->set(5, 5, 2, pho);
	matrix->set(6, 5, 0, 1.0);
	matrix->set(6, 7, 1, 1.0);
	matrix->set(6, 6, 2, 1.0);
	matrix->set(7, 3, 0, 1.0-phl);
	matrix->set(7, 7, 0, phl);
	matrix->set(7, 3, 1, 1.0-phl);
	matrix->set(7, 7, 1, phl);
	matrix->set(7, 3, 2, 1.0-phl);
	matrix->set(7, 7, 2, phl);
	matrix->set(8, 6, 0, 1.0-plh);
	matrix->set(8, 8, 0, plh);
	matrix->set(8, 6, 1, 1.0-plh);
	matrix->set(8, 8, 1, plh);
	matrix->set(8, 6, 2, 1.0-plh);
	matrix->set(8, 8, 2, plh);

	return matrix;
}





std::vector<Rewards*> generateEqualityConstraints()
{
	std::vector<Rewards*> v;
	return v;
}






std::vector<double> generateEqualityValues()
{
	std::vector<double> v;
	return v;
}





std::vector<Rewards*> generateInequalityConstraints()
{
	std::vector<Rewards*> constraint(1);
	constraint[0] = new Rewards(S, A);
	for (state_t i = 0; i < S; i++)
	{
		for (action_t j = 0; j < A; j++)
		{
			constraint[0]->setReward(i, j, 0.0);
			if (i == 3)
				constraint[0]->setReward(i, j, f1);
			if (i == 6)
				constraint[0]->setReward(i, j, f2);
		}
	}

	for (state_t i = 0; i < S; i++)
	{
		for (action_t j = 0; j<A; j++)
		{
			constraint[0]->setReward(i, j, -constraint[0]->getReward(i, j));
		}
	}


	return constraint;
}




std::vector<double> generateInequalityValues()
{
	std::vector<double> value(1, f3);
	value[0] = -value[0];
	return value;
}







































