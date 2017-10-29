/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */




#include <stdexcept>
#include <memory>

#include <gtest/gtest.h>
#include <mdp/stateSpace.h>
#include <mdp/stateSpaceDimension.h>
#include <mdp/priorityState.h>
#include <mdp/stateSpaceBuilder.h>
#include <mdp/domainModel.h>
#include "../state.h"

class Prio : public Mdp::PriorityState
{
public:
	std::string getName() override {return "";};
	bool isInState() override {return inState;};
	bool inState{false};
};

class Dimension : public Mdp::StateSpaceDimension
{
public:
	std::string getName() override {return "";};
	Mdp::statePosition_t getPosition() override {return position;};
	Mdp::statePosition_t position{0};
	size_t getNumberOfPositions() override {return nbOfPositions;};
	size_t nbOfPositions{2};
};

class TestDomainModel : public Mdp::DomainModel
{
public:
	double measureReward() override {return 3.14;};
};

Prio *prio1, *prio2;
Dimension *dim1, *dim2, *dim3;

double expectedReward = 3.14;
