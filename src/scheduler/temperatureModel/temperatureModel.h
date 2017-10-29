/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H

#include <string>
#include <tuple>
#include <vector>


namespace Scheduler
{

class TemperatureModel
{

public:
	virtual ~TemperatureModel(){};
	virtual double updateTemperature(double timeInterval, struct PowerParams *params, double taskPowerCoeff, double freq)=0;
	virtual void printTemperatureHistory(std::string filename)=0;
	virtual void printEnergyHistory(std::string filename)=0;
	virtual double getTemperature()=0;
};

struct PowerParams
{
	double voltage{1.0};
	double leakage{1.0};
	double capa{0.1};
	double power{0.0};
	double energy{0.0};
	bool powered{false};
};

}

#endif
