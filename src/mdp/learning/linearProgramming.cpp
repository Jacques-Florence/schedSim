/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "linearProgramming.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <mdp/constraintList.h>
#include <mdp/horizon.h>
#include <mdp/mdpConfiguration.h>
#include <mdp/policy.h>
#include <mdp/rewards.h>
#include <mdp/transitionMatrix.h>

#include "glpkImplementation.h"


using namespace Mdp;

void LinearProgramming::solve(Policy *policy, Rewards *rewards, ConstraintList *constraintList,
	TransitionMatrix *matrix, Horizon *horizon)
{

/*See references:
[1] "Robustness of policies in constrained Markov Decision Processes# by Zadorojniy ans Shwartz
[2] "Constrained Markov Decision Processes" by Altman
[3] "GNU Linear programming kit reference manual (November 2015)"
*/

	int S = policy->getNbOfStates();
	int A = policy->getNbOfActions();
	
	const size_t nbCol = S*A;
	columns = std::vector<double>(nbCol); //those are the rho(x,u) of [1], or x1 x2 x3 of [3]
	coeffs = std::vector<double>(nbCol); //c(x,u) of [1]
	objFunc = 0.0;

	prepareParameters(rewards, constraintList, matrix, horizon);
	//removeRedundantEqualityConstraint(0);
	//printParams();
	LpImplementation *solver = new GlpkImplementation(LpImplementation::LpAlgo::interiorPoint);
	objFunc = solver->solve(columns, coeffs, eqCoeffs, eqValue, ineqCoeffs, ineqValue);
	updatePolicy(policy);

}


void LinearProgramming::printParams()
{
	std::cout <<"printing coefficients\n";
	for (size_t i = 0; i < coeffs.size(); i++)
	{
		std::cout << coeffs[i]<<" ";
	}
	std::cout << "\n";
	std::cout << "printing eqCoeffs\n";
	for (size_t i = 0; i < eqCoeffs.size(); i++)
	{
		for (size_t j = 0; j < eqCoeffs[i].size(); j++ )
		{
			std::cout <<eqCoeffs[i][j]<< " ";
		}
		std::cout <<"\n";
	}
	std::cout << "eqValue:";
	for (size_t i = 0; i < eqValue.size(); i++)
	{
		std::cout << eqValue[i]<<" ";
	}
	std::cout << "\n";

	std::cout << "printing ineqCoeffs\n";
	for (size_t i = 0; i < ineqCoeffs.size(); i++)
	{
		for (size_t j = 0; j < ineqCoeffs[i].size(); j++ )
		{
			std::cout <<ineqCoeffs[i][j]<< " ";
		}
		std::cout <<"\n";
	}
	std::cout << "ineqValue:";
	for (size_t i = 0; i < ineqValue.size(); i++)
	{
		std::cout << ineqValue[i]<<" ";
	}
	std::cout << "\n";
	std::cout << "variables: ";
	for (size_t i = 0; i < columns.size(); i++)
	{
		std::cout << columns[i]<<" ";
	}
	std::cout <<"\n";
	std::cout << "objective function: "<<objFunc<<"\n";
}


void LinearProgramming::prepareParametersForDiscountedCost(Rewards *rewards, ConstraintList *constraintList,
	TransitionMatrix *matrix, double discount, std::vector<double> initialState)
{
	const size_t S = rewards->getNbOfStates();
	const size_t A = rewards->getNbOfActions();
	const size_t nbCol = S*A;
	for (state_t i = 0; i < S; i++)
	{
		for (action_t j = 0; j < A; j++)
		{
			coeffs[i*A + j] = -rewards->getReward(i, j); /*minus sign because cost, not reward*/
		}
	}
	size_t nbEqConst = S + 1;
	nbEqConst += constraintList->equalityConstraints.size();
	eqCoeffs = std::vector<std::vector<double>>(nbEqConst, std::vector<double>(nbCol));
	eqValue = std::vector<double>(nbEqConst);
	for (state_t i = 0; i < S; i++) //i is the x of 4.3 in [2].
	{
		for (state_t j = 0; j < S; j++)
		{
			for (action_t k = 0; k < A; k++)
			{
				double delta = 0.0;
				if (i == j)
					delta = 1.0;
				eqCoeffs[i][j*A+k] = delta - discount*matrix->get(j, i, k); //eq. 4.3 in [2]
			}
		}
		eqValue[i] = (1.0-discount)*initialState[i];
	}
	
	for (size_t i = S; i < S+1; i++) //this is executed only once
	{
		for (size_t j = 0; j < nbCol; j++)
		{
			eqCoeffs[i][j] = 1.0;
		}
		eqValue[i] = 1.0;	
	}
	
	for (size_t i = S+1; i < nbEqConst; i++ )
	{
		for (state_t j = 0; j < S; j++)
		{
			for (action_t k = 0; k < A; k++)
			{
				eqCoeffs[i][j*A+k] = constraintList->equalityConstraints[i-1-S]->getReward(j, k);
				/*although called reward, it's not a reward...*/
			}
		}
		eqValue[i] = constraintList->equalityValues[i-S-1];
	}

	size_t nbIneqConst = 0;
	nbIneqConst = constraintList->inequalityConstraints.size();
	ineqCoeffs = std::vector<std::vector<double>>(nbIneqConst, std::vector<double>(nbCol));
	ineqValue = std::vector<double>(nbIneqConst);
	/*remember that rho(y,u) >= 0 ([1]) is taken care of by the glpk solver*/
	for (size_t i = 0; i < nbIneqConst; i++ )
	{
		for (state_t j = 0; j < S; j++)
		{
			for (action_t k = 0; k < A; k++)
			{
				ineqCoeffs[i][j*A+k] = constraintList->inequalityConstraints[i]->getReward(j, k);
				/*although called reward, it's not a reward...*/
			}
		}
		ineqValue[i] = constraintList->inequalityValues[i];
	}

}









void LinearProgramming::updatePolicy(Policy *policy)
{
	const size_t S = policy->getNbOfStates();
	const size_t A = policy->getNbOfActions();
	std::vector<double> sum(S, 0.0);
	for (state_t i = 0; i < S; i++)
	{
		for (action_t j = 0; j < A; j++)
		{
			sum[i] += columns[i*A + j];
		}
	}
	const double epsilon = 0.000000001;
	for (state_t i = 0; i < S; i++)
	{
		if (sum[i] < epsilon)
		{
				std::vector<double> vector(A, 1.0/A);
				policy->update(i, vector);
		}
		else
		{
			std::vector<double> vector(A, 0.0);
			for (action_t j = 0; j < A; j++)
			{
				vector[j] = columns[i * A + j] / sum[i];
			}
			policy->update(i, vector);
		}
	}
}



void LinearProgramming::prepareParameters(Rewards *rewards, ConstraintList *constraintList,
	TransitionMatrix *matrix, Horizon *horizon)
{
	if (horizon->finiteHorizon == false)
	{
		prepareParametersForDiscountedCost(rewards, constraintList, matrix,
			horizon->discountFactor, horizon->initialStateDistribution);
	}
	else
	{
		throw std::runtime_error("Cost horizon type not supported");
	}
}


void LinearProgramming::removeRedundantEqualityConstraint(size_t index)
{
	eqCoeffs.erase(eqCoeffs.begin()+index);
	 eqValue.erase( eqValue.begin()+index);
}

































































































