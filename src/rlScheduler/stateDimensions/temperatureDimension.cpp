/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "temperatureDimension.h"

#include <cmath>
#include <stdexcept>

#include <scheduler/system.h>
#include <scheduler/processor.h>

using namespace RlScheduler;

std::string TemperatureDimension::getName()
{
	return "TemperatureDimension";
}

size_t TemperatureDimension::getNumberOfPositions()
{
	return nbOfPositions;
}


Mdp::statePosition_t TemperatureDimension::getPosition()
{
	double temp = Scheduler::System::getInstance()->getProc()->getTemperature();
	Mdp::statePosition_t ret = discretizePosition(temp);
	return ret;
}

Mdp::statePosition_t TemperatureDimension::discretizePosition(double temp) const
{
	if (temp < minTemp)
	{
		temp = minTemp;
	}
	if (temp > maxTemp)
	{
		temp = maxTemp;
	}
	double pos = temp - minTemp;
	pos /= maxTemp;
	pos *= ((double) nbOfPositions - 1.0);

	pos = floor(pos);
	return (Mdp::statePosition_t) pos;
}

