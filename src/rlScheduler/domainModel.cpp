/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "domainModel.h"

#include <cassert>
#include <iostream>
#include <limits>

#include <scheduler/system.h>
#include <scheduler/processor.h>
#include <scheduler/time.h>

#include "maxTempEstimator/maxTempEstimator.h"
#include "configuration.h"


#include <scheduler/temperatureModel/temperatureAndAgingModel.h>//TODO not good

using namespace RlScheduler;

DomainModel::DomainModel(std::shared_ptr<Configuration> c) :
	conf(c),
	tempRecord(c, "tempRecord"),
	maxTempRecord(c, "maxTempRecord")
{
	assert(conf != nullptr);
	deadlineMissRewardCoeff = conf->getDoubleValue("rlDiscipline", "deadlineMissRewardCoeff");
	temperatureRewardCoeff = conf->getDoubleValue("rlDiscipline", "tempRewardCoeff");
	agingRewardCoeff = conf->getDoubleValue("rlDiscipline", "agingRewardCoeff");
	maxTempEstimator = conf->getMaxTempEstimatorFromFile();

	usingThreshold = conf->getBoolValue("rlDiscipline", "usingThreshold", true);
}

DomainModel::~DomainModel()
{
}
void DomainModel::end()
{
	/*
	tempRecord.printToFile(".");
	maxTempRecord.printToFile(".");
	*/
	if (maxTempEstimator != nullptr)
		delete maxTempEstimator;
}

double DomainModel::measureReward()
{
	/*Deadline misses is updated in the rlDiscipline directly, 
	Let's add the temperature to it.*/
	double ret = deadlineMissRewardCoeff*reward - temperatureRewardCoeff*getTemperatureCost() - agingRewardCoeff*getAging();
	//if (getTemperatureCost() > 0.0 && reward > -1000000000)
	{
		//if (reward < -0.00000001 || reward > 0.0000001)
		{
			/*
			std::cerr << "reward is a+c*b = " << deadlineMissRewardCoeff*reward;
			std::cerr << "+" << temperatureRewardCoeff << "x" << getTemperatureCost() << "\n";
			*/
		}
	}
	return ret;
}

double DomainModel::getTemperatureCost()
{
#if 0
	return getInstantaneousTemp();
#endif
#if 0
#endif
	if (usingThreshold)
	{
		static const double tempLimit = conf->getTempLimit();
		double temp = getInstantaneousTemp();
		if (temp > tempLimit)
			return 1.0;
		return 0.0;
	}
	assert(maxTempEstimator != nullptr);
	return maxTempEstimator->getMaximumTemperature();
}

double DomainModel::getInstantaneousTemp()
{
	return Scheduler::System::getInstance()->getProc()->getTemperature();
}

double DomainModel::getAging()
{
	static double previousValue = 0.0;
	static double increment = 0.0;
	
	Scheduler::TemperatureAndAgingModel *model = dynamic_cast<Scheduler::TemperatureAndAgingModel*>(Scheduler::System::getInstance()->getProc()->getTemperatureModel());
	double cumul = model->getConsumedLifetime();
	increment = cumul - previousValue;
	previousValue = cumul;

	return increment;
}












