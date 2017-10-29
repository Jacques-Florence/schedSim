/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SCHEDULERDIMENSIONS_H
#define SCHEDULERDIMENSIONS_H

#include <memory>

#include <mdp/stateSpaceDimension.h>

namespace MdpGov
{

class SchedulerDomainModel;

class ReadyQueueDimension : public Mdp::StateSpaceDimension
{
public:
	static constexpr const char *configKey = "readyQueueSize";
public:
	~ReadyQueueDimension(){};
	std::string getName();
	Mdp::statePosition_t getPosition();
	size_t getNumberOfPositions();
};

class WaitQueueDimension : public Mdp::StateSpaceDimension
{
public:
	static constexpr const char *configKey = "waitQueueSize";
public:
	~WaitQueueDimension(){}
	std::string getName();
	Mdp::statePosition_t getPosition();
	size_t getNumberOfPositions();
};

class FrequencyDimension : public Mdp::StateSpaceDimension
{
public:
	static constexpr const char *configKey = "frequencyQueueSize";
public:
	~FrequencyDimension(){};
	std::string getName();
	Mdp::statePosition_t getPosition();
	size_t getNumberOfPositions();
};

class TemperatureDimension : public Mdp::StateSpaceDimension
{
public:
	static constexpr const char *configKey = "temperatureQueueSize";
public:
	~TemperatureDimension(){};
	std::string getName();
	Mdp::statePosition_t getPosition();
	size_t getNumberOfPositions();
};

class MissRateDimension : public Mdp::StateSpaceDimension
{
public:
	static constexpr const char *configKey = "missRateQueueSize";
public:
	~MissRateDimension(){};
	std::string getName();
	Mdp::statePosition_t getPosition();
	size_t getNumberOfPositions();
};


}

#endif
