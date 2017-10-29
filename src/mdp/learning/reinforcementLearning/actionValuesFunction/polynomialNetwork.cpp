/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "polynomialNetwork.h"

#include <iostream>
#include <stdexcept>

#include <mdp/context.h>

using namespace Mdp;


PolynomialNetwork::PolynomialNetwork(std::shared_ptr<Context> context, size_t I, size_t O, size_t H)
	: ApproximatedFunction(I, O, H*(I + O + 1))
	, hiddenSize(H)
	, hiddenLayer(std::vector<double>(H))
	, inputWeights(std::vector<std::vector<double>>(I+1, std::vector<double>(H, 0.0)))
	,outputWeights(std::vector<std::vector<double>>(H, std::vector<double>(O, 0.0)))
{
	inputSize++; //to account for the constant factor
	init(context);
}

void PolynomialNetwork::init(std::shared_ptr<Context> /*context*/)
{
}

std::vector<double> PolynomialNetwork::getParamVector()
{
	/*TODO*/
	return std::vector<double>();
}

void PolynomialNetwork::updateParameters(double /*coeff*/)
{
	/*TODO*/
	return;
}


void PolynomialNetwork::initializeWeights(std::vector<std::vector<double>> in,
                                          std::vector<std::vector<double>> out)
{
	inputWeights = in;
	outputWeights = out;
}

std::vector<double> PolynomialNetwork::getOutput(std::vector<double> input)
{
	input.push_back(1.0); //constant input
	hiddenLayer[0] = 1.0;
	for (size_t h = 1; h < hiddenSize; h++)
	{
		double sum = 0.0;
		for (size_t i = 0; i < inputSize; i++)
		{
			sum += input[i] * inputWeights[i][h];
		}
		double monome = 1;
		for (size_t e = 0; e < h; e++)
		{
			monome *= sum;
		}
		hiddenLayer[h] = monome;
	}
	std::vector<double> out = std::vector<double>(outputSize, 0.0);
	for (size_t o = 0; o < outputSize; o++)
	{
		for (size_t h = 0; h < hiddenSize; h++)
		{
			out[o] += hiddenLayer[h] * outputWeights[h][o];
			std::cerr << "o: " << o << " h: " << h << "outputweights: " << outputWeights[h][o] <<"\n";
		}
	}
	return out;
}



void PolynomialNetwork::learnExample(std::vector<double> /*input*/, std::vector<double> /*output*/)
{
	/*TODO*/
	/*double rate = 0.1;*/
}




double PolynomialNetwork::getValue(state_t /*s*/, action_t /*a*/)
{
	/*TODO*/
	throw std::logic_error("not implemented yet");
}


std::vector<double> PolynomialNetwork::getValues(state_t /*s*/)
{
	/*TODO*/
	throw std::logic_error("not implemented yet");
}


void PolynomialNetwork::setAlpha(double /*alpha*/)
{
	/*TODO*/
	throw std::logic_error("not implemented yet");
}
