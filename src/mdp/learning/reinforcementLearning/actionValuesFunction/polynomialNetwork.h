/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef POLYNOMIAL_NETWORK_H
#define POLYNOMIAL_NETWORK_H

#include "approximatedFunction.h"

namespace Mdp
{

struct context;

class PolynomialNetwork : public ApproximatedFunction
{
public:
	PolynomialNetwork(std::shared_ptr<Context> context, size_t inputSize, size_t outputSize, size_t nbOfHiddenLayers);
	std::vector<double> getParamVector() override;
	std::vector<double> getOutput(std::vector<double> input) override;
	void learnExample(std::vector<double> input, std::vector<double> output) override;
	void initializeWeights(std::vector<std::vector<double>>  inputWeights,
	                       std::vector<std::vector<double>> outputWeights);
	double getValue(state_t s, action_t a);
	std::vector<double> getValues(state_t s);
	void updateParameters(double coeff);
	void setAlpha(double alpha);
protected:
	void init(std::shared_ptr<Context> context);
	size_t hiddenSize{0};
	std::vector<double> hiddenLayer;
	std::vector<std::vector<double>> inputWeights;
	std::vector<std::vector<double>> outputWeights;
};

}

#endif
