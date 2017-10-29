/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <memory>

#include "approximatedFunction.h"
#include <doublefann.h>
#include <mdp/context.h>

namespace Mdp
{

class NeuralNetwork : public ApproximatedFunction
{
public:
	NeuralNetwork(std::shared_ptr<Context> context, size_t nbInputs, size_t nbHidden, size_t nbOutputs);
	~NeuralNetwork();
	std::vector<double> getOutput(std::vector<double> input) override;
	void learnExample(std::vector<double> input, std::vector<double> output) override;
	double getMse();
	virtual double getValue(state_t state, action_t action) override;
	virtual std::vector<double> getValues(state_t state) override;
	virtual void updateParameters(double coeff) override;
	virtual std::vector<double> getParameters();
	virtual void setAlpha(double alpha) override;
	size_t getNbInputs();
	size_t getNbHidden();
	size_t getNbOutputs();
	void setWeights(std::vector<double> weights);
protected:
	void init(std::shared_ptr<Context> context);
	struct fann *ann{nullptr};
	size_t nbInputs{0};
	size_t nbHidden{0};
	size_t nbOutputs{0};
	std::vector<double> getStateVector(state_t state);
	std::shared_ptr<Context> context{nullptr};
	void printWeights();
};
}

#endif
