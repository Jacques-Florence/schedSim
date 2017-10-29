/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "simpleTemperatureModel.h"

#include <cmath>
#include <iostream>
#include <utility>

#include <utils/log.h>

#include <scheduler/time.h>

using namespace Scheduler;


SimpleTemperatureModel::SimpleTemperatureModel(std::shared_ptr<Utils::Configuration> c)
	: R(c->getDoubleValue("scheduler", "thermalResistance"))
	, C(c->getDoubleValue("scheduler", "thermalCapacitance"))
	, temperatureHistory(Utils::Record(c, "temperature"))
	, energyHistory(Utils::Record(c, "energy"))
	, endTime(c->getDoubleValue("scheduler","runningTime"))
	, recordingTimeRatio(c->getDoubleValue("scheduler", "onlyLogTempAfterRatio"))
{
	logTemperature = c->getBoolValue("scheduler", "logTemperature", false);
	logEnergy = c->getBoolValue("scheduler", "logEnergy", false);
	std::cerr << "temperature and aging model initialized\n";
}

double SimpleTemperatureModel::updateTemperature(double timeInterval
                                               , struct PowerParams *params
                                               , double taskPowerCoeff
                                               , double freq)
{
	/*T(t) = [T0 - (Ta + RP)]exp(-t/(RC)) + (Ta + RP)*/
	Utils::Log log;
	if (params->powered)
	{
		params->power = params->voltage*params->voltage*freq*params->capa*taskPowerCoeff + params->leakage;
	}
	else
	{
		params->power = 0.0;
	}
	power = params->power;
	params->energy += params->power*timeInterval;
	computeAndLog();
	return T;
}


void SimpleTemperatureModel::printTemperatureHistory(std::string filename)
{
	if (logTemperature)
		temperatureHistory.printToFile(filename);
}

void SimpleTemperatureModel::printEnergyHistory(std::string filename)
{
	if (logEnergy)
		energyHistory.printToFile(filename);
}


void SimpleTemperatureModel::computeAndLog()
{
	double currentTime = Time::getTime();
	double timeInterval = currentTime - previousTime;
	previousTime = currentTime;
	A = Ta + R*power;
	T = (T0 - A)*exp(-timeInterval/(R*C)) + A;
	T0 = T;
	if (logTemperature)
	{
		if (Time::getTime() > recordingTimeRatio * endTime)
		{
			temperatureHistory.add(currentTime, T);
		}
	}
	if (logEnergy)
		energyHistory.add(currentTime, power);
}

double SimpleTemperatureModel::getTemperature()
{
	return T;
}

