/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "policy.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>

#include <utils/randomGenerator.h>
#include <utils/stringUtils.h>

using namespace Mdp;

Policy::Policy(int S, int A, std::shared_ptr<Utils::RandomGenerator> gen)
	: policy(std::vector<std::vector<double>>(S, std::vector<double>(A)))
	, nbOfStates(S)
	, nbOfActions(A)
	, randomGenerator(gen)
{
}



void Policy::initializeRandomly(std::shared_ptr<Utils::RandomGenerator> gen)
{
	for (state_t i = 0; i < nbOfStates; i++)
	{
		std::vector<double> vector = gen->drawDistribution(nbOfActions);
		update(i, vector);
	}
}

void Policy::initializeUniformly()
{
	for (state_t i = 0; i < nbOfStates; i++)
	{
		std::vector<double> vect(nbOfActions, 1.0/nbOfActions);
		update(i, vect);
	}
}

/*TODO: the format is not clear*/
void Policy::initializeFromFile(std::string filename)
{
	std::fstream stream;
	stream.open(filename);
	if (!stream.is_open())
		throw std::runtime_error("cannot open file");
	std::string line;
	std::vector<std::vector<double>> pol;
	while(std::getline(stream, line))
	{
		std::vector<std::string> elements = Utils::StringUtils::split(line, ' ');
		std::vector<double> row;
		/*TODO: this can be rewritten more elegantly*/
		for (size_t i = 0; i < elements.size(); i++)
		{
			row.push_back(std::stod(elements[i]));
		}
		pol.push_back(row);
	}
	policy = pol;
}

void Policy::saveToFile(std::string /*filename*/)
{
	/*FIXME: TODO*/
}


void Policy::update(state_t state, const std::vector<double> &vector)
{
        policy[state] = vector;
	/*
	std::cerr << "updating policy for state "<<state<<" with:";
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cerr << " " << vector[i];
	}
	std::cerr << "\n";
	*/
}


std::vector<double> *Policy::getActionVector(state_t state)
{
	return &policy[state];
}

action_t Policy::getAction(state_t state)
{
	std::vector<double> *vector = getActionVector(state);
	double d = randomGenerator->drawUniform(0.0, 1.0);
	double cumulative = 0.0;
	//std::cerr << "for state " << state <<", policy is:";
	for (action_t i = 0; i < vector->size(); i++)
	{
		//std::cerr << " " << (*vector)[i];
		cumulative += (*vector)[i];
		if (d <= cumulative)
		{
			return i;
		}
	}
	//std::cerr << "\n";
	handleErrorInGettingAction(vector, state, d);
	return 0;
}

void Policy::handleErrorInGettingAction(std::vector<double> *vector, state_t state, double d)
{
	std::cerr << "Bug occured. here is the action vector distribution for state ";
	std::cerr << state <<":\n";
	for (action_t i = 0; i < vector->size(); i++)
	{
		std::cerr << "    "<<(*vector)[i]<<"\n";
	}
	std::cerr << "d is "<<d<<"\n";
	throw std::runtime_error("Bug occured in selecting action from policy");
}



void Policy::print(std::ostream& /*stream*/)
{
#ifdef PRINT
	stream << "Printing the policy:\n";
	for (state_t i = 0; i < nbOfStates; i++)
	{
		for (action_t j = 0; j < nbOfActions; j++)
		{
			stream << policy[i][j] << "  ";
		}
		stream << "\n";
	}
#endif
}



size_t Policy::getNbOfStates()
{
	return nbOfStates;
}

size_t Policy::getNbOfActions()
{
	return nbOfActions;
}
















