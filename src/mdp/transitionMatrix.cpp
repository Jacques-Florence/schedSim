/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "transitionMatrix.h"

#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <utils/randomGenerator.h>



using namespace Mdp;


TransitionMatrix::TransitionMatrix(int S, int A) : nbOfStates(S), nbOfActions(A)
{
}

TransitionMatrix::~TransitionMatrix()
{
	if (matrix != nullptr)
		delete[] matrix;
}



double TransitionMatrix::get(state_t from, state_t to, action_t action)
{
	if (from >= nbOfStates || to >= nbOfStates || action >= nbOfStates)
		throw std::runtime_error("invalid value for matrix parameters");
	return getArray()[from*nbOfStates*nbOfActions + action*nbOfStates + to];
}

double TransitionMatrix::get(size_t stateAndAction, state_t to)
{
	if (stateAndAction >= nbOfStates*nbOfActions || to >= nbOfStates)
		throw std::runtime_error("invalid value for matrix parameters");
	return getArray()[stateAndAction * nbOfStates + to];
}


void TransitionMatrix::set(state_t from, state_t to, action_t action, double proba)
{
	if (from >= nbOfStates || to >= nbOfStates || action >= nbOfActions)
		throw std::runtime_error("invalid value for matrix parameters");
	getArray()[from*nbOfStates*nbOfActions + action*nbOfStates + to] = proba;
}


void TransitionMatrix::initializeRandomly(std::shared_ptr<Utils::RandomGenerator> gen)
{
	for (state_t i = 0; i < nbOfStates; i++)
	{
		for (action_t j = 0; j < nbOfActions; j++)
		{
			std::vector<double> vector = gen->drawDistribution(nbOfStates);
			for (state_t k = 0; k < nbOfStates; k++)
			{
				set(i, k, j, vector[k]);
			}
		}
	}
}


void TransitionMatrix::print(std::ostream& stream)
{
	if (matrix == nullptr)
	{
		stream << "(Transition matrix was not created)\n";
		return;
	}
	stream << "Transition Matrix:\n";
	for (state_t i = 0; i < nbOfStates; i++)
	{
		stream << "From state " << i <<"\n";
		for (action_t j = 0; j < nbOfActions; j++)
		{
			stream << "  With action " << j << ":  ";
			for (state_t k = 0; k < nbOfStates; k++)
			{
				stream << std::fixed << std::setfill(' ') << getArray()[i*nbOfActions*nbOfStates + j*nbOfStates + k] <<"  ";
			}
			stream << "\n";
		}
	}
}




double *TransitionMatrix::getArray()
{
	if (matrix == nullptr)
	{
		matrix = new double[nbOfStates*nbOfStates*nbOfActions];
	}
	return matrix;
}








