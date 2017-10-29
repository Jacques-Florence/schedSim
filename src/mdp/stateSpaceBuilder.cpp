/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "stateSpaceBuilder.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "priorityState.h"
#include "stateSpace.h"
#include "stateSpaceDimension.h"

using namespace Mdp;

std::shared_ptr<StateSpace> StateSpaceBuilder::getStateSpace()
{
	throwIfNoModel();
	throwIfInconsistentNumberOfStates();
	/*if nbOfStates is 1, it means no dimension has been added to the state space, and therefore we only have priority states.*/
	if (nbOfStates == 1)
		nbOfStates = 0;
	std::shared_ptr<StateSpace> stateSpace(new StateSpace(nbOfStates, nbOfPriorityStates, dimensions, priorityStates));
	stateSpace->domainModel = domainModel; /*TODO: is this necessary?*/
	return stateSpace;
}

void StateSpaceBuilder::addDimension(StateSpaceDimension *dim)
{
	/*TODO: check that this dimension was not added twice*/
	throwIfNoModel();
	dim->domainModel = domainModel;
	dim->setIndex(nbOfDimensions++);
	nbOfStates *= dim->getNumberOfPositions();
	assert(nbOfStates >= 0); //getNumberOfPositions returns -1 if not defined
	dimensions.push_back(dim);
}
void StateSpaceBuilder::setDomainModel(std::shared_ptr<DomainModel> model)
{
	domainModel = model;
	if (domainModel == nullptr)
		throw std::runtime_error("domainModel is null");
}

void StateSpaceBuilder::throwIfInconsistentNumberOfStates()
{
	if (nbOfStates == 1 && nbOfDimensions == 0)
	{
		if (nbOfPriorityStates == 0)
			throw std::runtime_error("StateSpace has no states defined");
		if (nbOfPriorityStates == 1)
			throw std::runtime_error("State space has no dimensions and only one priority state");
	}
	if (nbOfStates > 1 && nbOfDimensions > 0)
	{
		return;
	}
	if (nbOfStates == 1 && nbOfDimensions > 0)
	{
		throw std::runtime_error("The state space has dimensions but all have only one state position");
	}
	if (nbOfStates == 0 && nbOfDimensions > 0)
	{
		throw std::runtime_error("A statespace dimension has zero state positions");
	}
}

void StateSpaceBuilder::throwIfNoModel()
{
	if (domainModel == nullptr)
	{
		throw std::runtime_error("no domain model specified");
	}
}

void StateSpaceBuilder::addPriorityState(PriorityState *prio)
{
	/*TODO check this state was not added twice*/
	throwIfNoModel();
	prio->domainModel = domainModel;
	nbOfPriorityStates++;
	priorityStates.push_back(prio);
}
