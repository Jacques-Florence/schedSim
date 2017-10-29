/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "tabularActionValues.h"

#include <cassert>
#include <stdexcept>
#include <fstream>
#include <iostream>

#include <utils/stringUtils.h>
#include <utils/randomGenerator.h>

#include <mdp/stateSpace.h>
#include <mdp/actionSpace.h>
#include <mdp/mdpConfiguration.h>

using namespace Mdp;

TabularActionValues::TabularActionValues(std::shared_ptr<Context> context)
{
	init(context);
}

std::vector<std::vector<double>> TabularActionValues::fromFile(size_t S, size_t A, std::string filename)
{
	std::ifstream stream;
	stream.open(filename);
	if (!stream.is_open())
		throw std::runtime_error("cannot open action values file");
	std::string line;
	std::vector<std::vector<double>> av;
	while(std::getline(stream, line))
	{
		std::vector<std::string> vect = Utils::StringUtils::split(line, ' ');
		if (vect.size() > 0)
		{
			if (vect.size() != A)
				throw std::runtime_error(
					"number of values not equal to number of actions");
			std::vector<double> row(A);
			for (size_t i = 0; i < A; i++)
				row[i] = std::stod(vect[i]);
			av.push_back(row);
		}
	}
	if (av.size() != S)
		throw std::runtime_error(
			"The number of lines in the file is not equal to the nnumber of states");
	return av;
}






std::vector<std::vector<double>> TabularActionValues::randomly(size_t S, size_t A, time_t seed, double lowerBound, double upperBound)
{
	if (lowerBound > upperBound)
	{
		throw std::invalid_argument("The lower bound is greater than the upper bound");
	}
	Utils::RandomGenerator gen = Utils::RandomGenerator(seed);
	std::vector<std::vector<double>> av(S, std::vector<double>(A));
	for (size_t s = 0; s < S; s++)
	{
		for (size_t a = 0; a < A; a++)
		{
			av[s][a] = gen.drawUniform(lowerBound, upperBound);
		}
	}
	return av;
}

std::vector<std::vector<double>> TabularActionValues::uniformly(size_t S, size_t A, double value)
{
	std::vector<std::vector<double>> av(S, std::vector<double>(A, value));
	return av;
}

void TabularActionValues::init(std::shared_ptr<Context> context)
{
	size_t S = context->stateSpace->size();
	size_t A = context->actionSpace->size();

	std::string str = context->conf->getStringValue("reinforcementLearning", "actionValuesInitialization");
	if (!str.compare("uniform"))
	{
		double initialAV = context->conf->getDoubleValue("reinforcementLearning", "initialActionValue");
		actionValues = uniformly(S, A, initialAV);
	}
	else if (!str.compare("fromFile"))
	{
		actionValues = fromFile(S, A, "configuration/initialActionValues");
	}
	else if (!str.compare("random"))
	{
		time_t seed = context->conf->getIntValue("reinforcementLearning", "seed");
		double lowerBound = context->conf->getDoubleValue("reinforcementLearning", "lowerBound");
		double upperBound = context->conf->getDoubleValue("reinforcementLearning", "upperBound");
		actionValues = randomly(S, A, seed, lowerBound, upperBound);
	}
	else
	{
		throw std::invalid_argument("invalid value for actionValuesInitialization");
	}
}



double TabularActionValues::getValue(state_t s, action_t a)
{
	assert(s < actionValues.size());
	assert(a < actionValues[s].size());
	return actionValues[s][a];
}

void TabularActionValues::updateValue(state_t s, action_t a, double value)
{
	actionValues[s][a] = value;
}

size_t TabularActionValues::size()
{
	return actionValues.size();
}


std::vector<double> TabularActionValues::getValues(state_t state)
{
	return actionValues[state];
}
