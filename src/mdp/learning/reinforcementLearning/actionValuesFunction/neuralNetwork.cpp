/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "neuralNetwork.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <memory>

#include <doublefann.h>

#include <mdp/context.h>
#include <mdp/stateSpace.h>


using namespace Mdp;

NeuralNetwork::NeuralNetwork(std::shared_ptr<Context> context, size_t i, size_t h, size_t o)
	: ApproximatedFunction(i, (i+o)*h, o)
	, nbInputs(i)
	, nbHidden(h)
	, nbOutputs(o)
{
	ann = fann_create_standard(3, nbInputs, nbHidden, nbOutputs);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_LINEAR);
	fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
	fann_set_learning_rate(ann, 0.5);
	init(context);
}

void NeuralNetwork::init(std::shared_ptr<Context> c)
{
	context = c;
}


NeuralNetwork::~NeuralNetwork()
{
	fann_destroy(ann);
}

std::vector<double> NeuralNetwork::getOutput(std::vector<double> input)
{
	double *out = fann_run(ann, &input[0]); //do not free
	std::vector<double> output(nbOutputs);
	for (size_t i = 0; i < nbOutputs; i++)
	{
		output[i] = out[i];
	}
	return output;
}

void NeuralNetwork::learnExample(std::vector<double> input, std::vector<double> output)
{
	assert(input.size() == nbInputs);
	assert(output.size() == nbOutputs);
	fann_train(ann, &input[0], &output[0]);
	printWeights();
}

void NeuralNetwork::printWeights()
{

	static std::vector<double> previousWeights;
	static long long unsigned int counter = 0;
	counter++;
	if (counter >= 10000)
	{
		counter = 0;
		std::vector<double> weights = getParameters();
		std::ostringstream stream;
		bool display = false;
		int colCounter = 0;
		for (size_t i = 0; i < weights.size(); i++)
		{
			if (previousWeights.size() > 0)
			{
				if (weights[i] > previousWeights[i] || weights[i] < previousWeights[i])
				{
					display = true;
					stream << "\033[1;31m";
				}
			}
			stream << weights[i] << "\033[0m" << " ";
			colCounter++;
			if (colCounter == 15)
			{
				colCounter = 0;
				stream << "\n";
			}
		}
		stream << "\n\n";
		if (display)
		{
			std::cerr << "\033[2J" << "\033[1;1H" << std::setprecision(2) << std::fixed << std::scientific;
			std::cerr << stream.str();
		}
		previousWeights = weights;
	}
}


double NeuralNetwork::getMse()
{
	return (double) fann_get_MSE(ann);
}


void NeuralNetwork::updateParameters(double /*coeff*/)
{
	throw std::logic_error("not implemented yet");
}


std::vector<double> NeuralNetwork::getValues(state_t state)
{
	return getOutput(getStateVector(state));
}

double NeuralNetwork::getValue(state_t state, action_t action)
{
	std::vector<double> vect = getValues(state);
	return vect[action];
}

std::vector<double> NeuralNetwork::getStateVector(state_t state)
{
	assert(context != nullptr);
	static std::vector<size_t> *vect;
	vect = context->stateSpace->factorize(state);
	static std::vector<double> retval(vect->size());
	for (size_t i = 0; i < vect->size(); i++)
	{
		retval[i] = (double) (*vect)[i];
	}
	return retval;
}


void NeuralNetwork::setAlpha(double alpha)
{
	//std::cerr << "alpha was: "<< fann_get_learning_rate(ann) <<"\n";
	fann_set_learning_rate(ann, alpha);
	//std::cerr << "alpha set to: " << alpha << "\n";
	//std::cerr << "alpha is: " << fann_get_learning_rate(ann) <<"\n";
}


std::vector<double> NeuralNetwork::getParameters()
{
	unsigned int connectionNumber = fann_get_total_connections(ann);
	static struct fann_connection *connections = new struct fann_connection[connectionNumber];
	fann_get_connection_array(ann, connections);
	static std::vector<double> ret(connectionNumber);
	for (unsigned int i = 0; i  < connectionNumber; i++)
	{
		ret[i] = connections[i].weight;
	}
	return ret;
}

void NeuralNetwork::setWeights(std::vector<double> weights)
{
	unsigned int connectionsNumber = fann_get_total_connections(ann);
	static struct fann_connection *connections = new struct fann_connection[connectionsNumber];
	fann_get_connection_array(ann, connections);
	for (size_t i = 0; i < connectionsNumber; i++)
	{
		connections[i].weight = weights[i];
	}
	fann_set_weight_array(ann, connections, connectionsNumber);
}


size_t NeuralNetwork::getNbInputs()
{
	return nbInputs;
}
size_t NeuralNetwork::getNbHidden()
{
	return nbHidden;
}
size_t NeuralNetwork::getNbOutputs()
{
	return nbOutputs;
}



#if 0
void NeuralNetwork::printParameters()
{
	throw std::logic_error("printParameters() not implemented yet");
}
#endif
