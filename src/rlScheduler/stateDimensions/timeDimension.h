/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_SCHEDULER_TIME_DIMENSION_H
#define RL_SCHEDULER_TIME_DIMENSION_H

#include <vector>

#include <mdp/stateSpaceDimension.h>

namespace RlScheduler
{

class TimeDimension : public Mdp::StateSpaceDimension
{
public:
	TimeDimension(int nbOfPositions);
	std::string getName() override;
	Mdp::statePosition_t getPosition() override;
	size_t getNumberOfPositions() override;
private:
	int counter{0};
	size_t nbOfPositions;
};


}



#endif
