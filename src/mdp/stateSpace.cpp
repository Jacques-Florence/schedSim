/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "stateSpace.h"

#include <iostream>
#include <cassert>
#include <stdexcept>

#include "priorityState.h"
#include "transitionMatrix.h"
#include "rewards.h"
#include "action_impl.h"
#include "domainModel.h"

using namespace Mdp;


StateSpace::StateSpace(size_t N, size_t Nprio, std::vector<StateSpaceDimension *> dims, std::vector<PriorityState *> prio)
	: nbOfStates(N)
	, nbOfPriorityStates(Nprio)
	, dimensions(dims)
	, priorityStates(prio)
	, internalState(std::vector<int>(dimensions.size()))
{
}

StateSpace::~StateSpace()
{
	for (size_t i = 0; i < dimensions.size(); i++)
	{
		delete dimensions[i];
	}
}

void StateSpace::updateInternalState()
{
	//embarassingly parallelizable
	for (unsigned int i = 0; i < dimensions.size(); i++)
	{
		StateSpaceDimension *dim = dimensions[i];
		assert(dim != nullptr);
		statePosition_t pos = dim->getPosition();
		internalState[dim->getIndex()] = pos;
	}
}

state_t StateSpace::getState()
{
	return currentExternalState;
}

void StateSpace::updateCurrentState()
{
	int prio = getPriorityStateInternal();
	state_t state;
	if (prio != -1)
	{
		state = nbOfStates + prio;
	}
	else
	{
		updateInternalState();
		state = convertState(internalState);
	}
	currentExternalState = state;
}

size_t StateSpace::getNbOfDimensions()
{
	/*FIXME: how to include priority states?*/
	return dimensions.size();
}

std::vector<size_t> *StateSpace::factorize(state_t state)
{
	static size_t size = dimensions.size();
	static std::vector<size_t> vect(size);
#if 1
	static bool init = false;
	assert(size >= 1);
	static std::vector<int> multVect(size);
	if (!init)
	{
		multVect[0] = 1;
		for (size_t i = 0; i < size-1; i++)
		{
			multVect[i+1] = multVect[i]*dimensions[i]->getNumberOfPositions();
		}
		init = true;
	}
	for (ssize_t i = size-1; i >= 0; i--)
	{
		vect[i] = state/multVect[i];
		state %= multVect[i];
	}
#else
	unsigned int multiplicator = 1;
	for (size_t i = 0; i < size; i++)
	{
		multiplicator *= dimensions[i]->getNumberOfPositions();
	}
	for (ssize_t i = size-1; i >= 0; i--)
	{
		multiplicator /= dimensions[i]->getNumberOfPositions();
		vect[i] = state / multiplicator;
		state = state % multiplicator;
	}
#endif
	return &vect;
}


std::vector<size_t> StateSpace::getDimensionSizes()
{
	std::vector<size_t> vect(dimensions.size());
	for (size_t i = 0; i < dimensions.size(); i++)
	{
		vect[i] = dimensions[i]->getNumberOfPositions(); //FIXME: what about priority states ?
	}
	return vect;
}



state_t StateSpace::convertState(StateInternal iState)
{
	state_t state = 0;
	unsigned int multiplicator = 1;
	state_t added = 0;
	static size_t size = dimensions.size();
	for (size_t i = 0; i < size; i++)
	{
		added = iState[i]; /*I think the index should be the same as i ?*/
		state += added * multiplicator;
		multiplicator *= dimensions[i]->getNumberOfPositions();
		if (multiplicator <= 0)
			throw std::runtime_error("The number of positions of one of the dimensions is not positive");
	}
	return state;
}


int StateSpace::getPriorityStateInternal()
{
	for (size_t i = 0; i < priorityStates.size(); i++)
	{
		if (priorityStates[i]->isInState())
			return i;
	}
	return -1;
}

size_t StateSpace::size()
{
	return nbOfStates + nbOfPriorityStates;
}


double StateSpace::getReward()
{
	return domainModel->measureReward();
}









