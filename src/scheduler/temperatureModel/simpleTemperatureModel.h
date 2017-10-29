/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SIMPLETEMPERATUREMODEL_H
#define SIMPLETEMPERATUREMODEL_H

#include <string>
#include <utility>

#include <utils/configuration.h>

#include "temperatureModel.h"
#include <scheduler/processor.h>

namespace Scheduler
{

class SimpleTemperatureModel : public TemperatureModel
{
public:
	static constexpr const char *configKey = "simpleTemperatureModel";
public:
	SimpleTemperatureModel(std::shared_ptr<Utils::Configuration> conf);
	virtual ~SimpleTemperatureModel(){};
	double updateTemperature(double timeInterval, struct PowerParams *params,
		double taskPowerCoeff, double freq) override;
	void printTemperatureHistory(std::string filename) override;
	void printEnergyHistory(std::string filename) override;
	double getTemperature() override;
private:
	double T0{20.0}; /*previous temperature*/
	const double Ta{20.0}; /*ambient temperature*/
	const double R{1.5}; /*thermal resistance*/
	const double C{150}; /*thermal capacity*/
	double A{0.0};
	double T{0.0};
	double power{0.0};
	double previousTime{0.0};
	Utils::Record temperatureHistory;
	Utils::Record energyHistory;
	bool logTemperature{false};
	bool logEnergy{false};
	const double endTime{0.0};
	double recordingTimeRatio{0.0};
	void computeAndLog();
};

}



#endif
