/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <mdp/stateSpaceDimension.h>





namespace Gridworld
{

class StateSpaceDimension : public Mdp::StateSpaceDimension
{
public:
	StateSpaceDimension(size_t size);
	std::string getName() override;
	statePosition_t getPosition() override;
	size_t getNumberOfPositions() override;
};

class XDimension : public StateSpaceDimension
{
public:
	XDimension(size_t size) StateSpaceDimension(size);
};

class YDimension : public StateSpaceDimension
{
public:
	YDimension(size_t size) StateSpaceDimension(size);
};

}



