/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef APPROXIMATED_FUNCTION_H
#define APPROXIMATED_FUNCTION_H

#include <cstddef>
#include <vector>

#include "actionValuesFunction.h"

namespace Mdp
{

struct Context;

class ApproximatedFunction : public ActionValuesFunction
{
public:
	ApproximatedFunction(size_t inputSize, size_t outputSize, size_t paramSize);
	virtual std::vector<double> getParamVector();
	virtual std::vector<double> getOutput(std::vector<double> input)=0;
	virtual void learnExample(std::vector<double> input, std::vector<double> output)=0;
	virtual void updateParameters(double coeff)=0;
	virtual double getValue(state_t state, action_t action)=0;
	virtual std::vector<double> getValues(state_t state)=0;
	virtual void setAlpha(double alpha)=0;
protected:
	size_t inputSize{0};
	size_t outputSize{0};
	size_t paramSize{0};
	std::vector<double> params;
};

}


#endif
