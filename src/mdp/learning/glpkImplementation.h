/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef GLPKIMPLEMENTATION_H
#define GLPKIMPLEMENTATION_H

#include "lpImplementation.h"

class glp_prob;

namespace Mdp
{


class GlpkImplementation : public LpImplementation 
{
public:
	GlpkImplementation(LpImplementation::LpAlgo algo) : algorithm(algo){};
	~GlpkImplementation(){};
	
	double solve(std::vector<double>& variables,
	             std::vector<double> coeffs,
	             std::vector<std::vector<double>> eqCoeffs,
	             std::vector<double> eqValue,
	             std::vector<std::vector<double>> ineqCoeffs,
	             std::vector<double> ineqValue);
private:
	LpImplementation::LpAlgo algorithm;
	double simplexSolve(glp_prob *lp, std::vector<double>& variables);
	double interiorPointSolve(glp_prob *lp, std::vector<double>& variables);
};


}
#endif
