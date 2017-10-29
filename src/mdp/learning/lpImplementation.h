/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef LPIMPLEMENTATION_H
#define LPIMPLEMENTATION_H

#include <vector>

namespace Mdp //maybe linear programming deserves its own namespace?
{

class LpImplementation
{
public:
	enum LpAlgo {simplex, interiorPoint};
	
	LpImplementation(LpImplementation::LpAlgo){};
	virtual ~LpImplementation(){};
	virtual double solve(std::vector<double>& variables,
	             std::vector<double> coeffs,
	             std::vector<std::vector<double>> eqCoeffs,
	             std::vector<double> eqValue,
	             std::vector<std::vector<double>> ineqCoeffs,
	             std::vector<double> ineqValue)=0;
protected:
	LpImplementation(){};
};





}




#endif
