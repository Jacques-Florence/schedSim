/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_SCHEDULER_TEMPERATURE_DIMENSION_H
#define RL_SCHEDULER_TEMPERATURE_DIMENSION_H

#include <mdp/stateSpaceDimension.h>

namespace RlScheduler
{

class TemperatureDimension : public Mdp::StateSpaceDimension
{
public:
	TemperatureDimension(int nbPos) : nbOfPositions(nbPos) {};
	std::string getName() override;
	Mdp::statePosition_t getPosition() override;
	size_t getNumberOfPositions() override;
	
private:
	Mdp::statePosition_t discretizePosition(double temperature) const;
	size_t nbOfPositions{800}; //arbitrary number
	double minTemp{20};
	double maxTemp{55};
};

}

#endif
