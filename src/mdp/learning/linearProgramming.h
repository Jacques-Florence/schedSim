/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef LINEARPROGRAMMING_H
#define LINEARPROGRAMMING_H

#include "solver.h"

#include <vector>

#include <mdp/mdpConfiguration.h>

namespace Mdp
{


class Policy;
class Rewards;
class ConstraintList;
class TransitionMatrix;
class Horizon;

class LinearProgramming : public Solver
{
public:
	static constexpr const char *configKey = "linearProgramming";
public:
	LinearProgramming(Utils::Configuration *c) : conf(c){};
	~LinearProgramming(){};
	void solve(Policy *policy, Rewards *rewards, ConstraintList *constraintList, TransitionMatrix *matrix, Horizon *horizon);
private:
	void prepareParameters(Rewards *rewards, ConstraintList *constraintList, TransitionMatrix *matrix, Horizon *horizon);
	void prepareParametersForDiscountedCost(Rewards *rewards, ConstraintList *constraintList, TransitionMatrix *matrix,
		double discountFactor, std::vector<double> initialStateDistribution);
	void removeRedundantEqualityConstraint(size_t index);
	void solveLinearProgram();
	void updatePolicy(Policy *policy);
	void printParams();

	double objFunc;
	std::vector<double> columns;
	std::vector<double> coeffs;
	std::vector<std::vector<double>> eqCoeffs;
	std::vector<double> eqValue;
	std::vector<std::vector<double>> ineqCoeffs;
	std::vector<double> ineqValue;
	Utils::Configuration *conf;
	
};


}
#endif
