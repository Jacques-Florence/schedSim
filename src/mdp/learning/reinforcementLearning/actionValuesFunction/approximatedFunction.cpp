/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "approximatedFunction.h"

using namespace Mdp;


ApproximatedFunction::ApproximatedFunction(size_t i, size_t o, size_t p)
	: inputSize(i)
	, outputSize(o)
	, paramSize(p)
	, params(std::vector<double>(p, 0.0))
{
}

std::vector<double> ApproximatedFunction::getParamVector()
{
	return params;
}




