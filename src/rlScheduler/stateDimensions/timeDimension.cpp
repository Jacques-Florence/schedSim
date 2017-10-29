/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "timeDimension.h"

#include <cassert>
#include <cmath>

#include <scheduler/system.h>

using namespace RlScheduler;


TimeDimension::TimeDimension(int n) : nbOfPositions(n)
{
}


std::string TimeDimension::getName()
{
	return "Time dimension";
}

Mdp::statePosition_t TimeDimension::getPosition()
{
	long long int jobArrivalCounter = Scheduler::System::getInstance()->getJobsArrivalCount();

	
	return (jobArrivalCounter % nbOfPositions);
}

size_t TimeDimension::getNumberOfPositions()
{
	return nbOfPositions;
}
