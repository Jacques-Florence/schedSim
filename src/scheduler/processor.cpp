/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "processor.h"

#include <iomanip>
#include <iostream>
#include <fstream>

#include <utils/log.h>

#include "time.h"
#include "process.h"
#include "temperatureModel/temperatureModel.h"

using namespace Scheduler;

//TODO: make the Utils::Record use a shared_ptr so we don't need get()
Processor::Processor(std::shared_ptr<Utils::Configuration> c) : conf(c), usageHistory(Utils::Record(c, "usage")), freqHistory(Utils::Record(c, "frequency"))
{
}

Processor::~Processor()
{
	delete temperatureModel;
}

double Processor::getMaxFreq() const
{
	return maxFreq;
}

double Processor::getMinFreq() const
{
	return minFreq;
}

double Processor::getUsage() const
{
	return usage;
}

void Processor::updateUsage()
{
	long long int deltaIdle = totalIdleTicks - previousIdleTicks;
	long long int deltaBusy = totalBusyTicks - previousBusyTicks;
	previousIdleTicks = totalIdleTicks;
	previousBusyTicks = totalBusyTicks;
	long long int sumDelta = deltaIdle + deltaBusy;
	if (sumDelta == 0)
	{
		usage = 0.0;
	}
	else
	{
		usage = (double)deltaBusy/(double)sumDelta;
	}
	usageHistory.add(Time::getTime(), usage);
}

void Processor::reinitTicks()
{
	totalBusyTicks = totalIdleTicks = 0;
}

bool Processor::isBusy() const
{
	return (runningTask != nullptr);
}


bool Processor::isRunning(std::shared_ptr<Process> p) const
{
	return (runningTask == p);
}


void Processor::setRunning(std::shared_ptr<Process> p)
{
	runningTask = p;
}




std::shared_ptr<Process> Processor::getRunningTask()
{
	return runningTask;
}




void Processor::updateTemperature(double timeInterval)
{
	/*FIXME where should the powerCoeff of an idle processor be defined?*/
	double powerCoeff = (runningTask==nullptr) ? 0.0: runningTask->powerCoeff;

	temperatureModel->updateTemperature(timeInterval, &powerParams, powerCoeff, freq);

}



void Processor::setTemperatureModel(TemperatureModel *model)
{
	temperatureModel = model;
}

TemperatureModel *Processor::getTemperatureModel()
{
	return temperatureModel;
}

void Processor::setFreq(double f)
{
	double epsilon = 0.0000001;
	if (f < (freq - epsilon) || (f > freq + epsilon))
		freqHistory.add(Time::getTime(), f);
	freq = f;
}


double Processor::getFreq() const
{
	return freq;
}



void Processor::printTemperatureReport(std::string folder) const
{
	temperatureModel->printTemperatureHistory(folder);
}

void Processor::printEnergyReport(std::string folder) const
{
	temperatureModel->printEnergyHistory(folder);
}




void Processor::printUsageReport(std::string folder) const
{
	usageHistory.printToFile(folder);
}

void Processor::printFreqReport(std::string folder) const
{
	freqHistory.printToFile(folder);
}

void Processor::printReports(std::string folder) const
{
	printTemperatureReport(folder);
	printEnergyReport(folder);
	printUsageReport(folder);
	printFreqReport(folder);
}


void Processor::updateTicks()
{
	busy ? (totalBusyTicks++) : (totalIdleTicks++);
}

void Processor::power(bool b) 
{
	powerParams.powered = b;
}

bool Processor::powered() const
{
	return powerParams.powered;
}


double Processor::getTemperature() const
{
	return temperatureModel->getTemperature();
}




