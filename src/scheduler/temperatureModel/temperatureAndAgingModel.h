/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TEMPERATURE_AND_AGING_MODEL_H
#define TEMPERATURE_AND_AGING_MODEL_H

#include <string>
#include <utility>

#include <utils/configuration.h>

#include "temperatureModel.h"
#include <scheduler/processor.h>

namespace Scheduler
{

class TemperatureAndAgingModel : public TemperatureModel
{
public:
	static constexpr const char *configKey = "temperatureAndAging";
public:
	TemperatureAndAgingModel(std::shared_ptr<Utils::Configuration> conf);
	virtual ~TemperatureAndAgingModel(){};
	double updateTemperature(double timeInterval, struct PowerParams *params,
		double taskPowerCoeff, double freq) override;
	void printTemperatureHistory(std::string filename) override;
	void printEnergyHistory(std::string filename) override;
	double getTemperature() override;
	double getConsumedLifetime();
private:
	static const constexpr double k = 8.617/100000;//Boltzmann constant in eV/K
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
	Utils::Record instantaneousAgingHistory;
	Utils::Record cumulativeAgingHistory;
	bool logTemperature{false};
	bool logEnergy{false};
	bool logAging{false};
	const double endTime{0.0};
	double recordingTimeRatio{0.0};

	double consumedLifetime{0.0};
	const double activationEnergy{0.0}; //to be expressed in eV
	const double formFactor{0.0};

	void computeAndLog();
	void computeAging();
};

}



#endif
