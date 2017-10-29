/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "temperatureAndAgingModel.h"

#include <cmath>
#include <iostream>
#include <utility>

#include <utils/log.h>

#include <scheduler/time.h>

using namespace Scheduler;


TemperatureAndAgingModel::TemperatureAndAgingModel(std::shared_ptr<Utils::Configuration> c)
	: R(c->getDoubleValue("scheduler", "thermalResistance"))
	, C(c->getDoubleValue("scheduler", "thermalCapacitance"))
	, temperatureHistory(Utils::Record(c, "temperature"))
	, energyHistory(Utils::Record(c, "energy"))
	, instantaneousAgingHistory(Utils::Record(c, "instantaneousAging"))
	, cumulativeAgingHistory(Utils::Record(c, "cumulativeAging"))
	, endTime(c->getDoubleValue("scheduler","runningTime"))
	, recordingTimeRatio(c->getDoubleValue("scheduler", "onlyLogTempAfterRatio"))
	, activationEnergy(c->getDoubleValue("scheduler", "activationEnergy"))
	, formFactor(c->getDoubleValue("scheduler", "formFactor"))
{
	logTemperature = c->getBoolValue("scheduler", "logTemperature", false);
	logEnergy = c->getBoolValue("scheduler", "logEnergy", false);
	logAging = c->getBoolValue("scheduler", "logAging", false);
}

double TemperatureAndAgingModel::updateTemperature(double timeInterval
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
	computeAndLog(); //TODO not good
	computeAging();
	return T;
}


void TemperatureAndAgingModel::printTemperatureHistory(std::string filename)
{
	if (logTemperature)
		temperatureHistory.printToFile(filename);
	if (logAging)
		instantaneousAgingHistory.printToFile(filename);
}

void TemperatureAndAgingModel::printEnergyHistory(std::string filename)
{
	if (logEnergy)
		energyHistory.printToFile(filename);
}


void TemperatureAndAgingModel::computeAndLog()
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

double TemperatureAndAgingModel::getTemperature()
{
	return T;
}


void TemperatureAndAgingModel::computeAging()
{
	static double previousTime = 0.0;
	//static double previousTemp = 0.0;
	static double currentTime = 0.0;
	static double previousRate = 0.0;
	static double currentRate = 0.0;

	currentTime = Time::getTime();
	
	double Tk = T + 273.15; //Celsius to Kelvin

	currentRate = exp(-activationEnergy/(k*Tk))/(k*Tk);

	/*Trapezoidal rule integration*/
	double a = (currentRate + previousRate)*(currentTime - previousTime)/2.0;
	consumedLifetime += a;

	previousTime = currentTime;
	previousRate = currentRate;
	if (logAging)
		instantaneousAgingHistory.add(currentTime, a);
}

double TemperatureAndAgingModel::getConsumedLifetime()
{
	return consumedLifetime;
}


















