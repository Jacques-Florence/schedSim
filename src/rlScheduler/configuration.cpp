/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "configuration.h"
#include "rlDiscipline.h"

#include "maxTempEstimator/envelopeDetector.h"
#include "maxTempEstimator/exponentialMaxTempEstimator.h"
#include "maxTempEstimator/squareMaxTempEstimator.h"
#include "maxTempEstimator/monomialMaxTempEstimator.h"

#include <memory>

using namespace RlScheduler;

std::unique_ptr<Scheduler::SchedulingDiscipline> Configuration::getDisciplineFromFile()
{
	std::unique_ptr<Scheduler::SchedulingDiscipline> discipline = SchedulerConfiguration::getDisciplineFromFile();
	if (discipline == nullptr)
	{
		std::string value = getStringValue("scheduler", "discipline");
		if (!value.compare(RlDiscipline::configKey))
			discipline = std::make_unique<RlDiscipline>(std::dynamic_pointer_cast<Configuration>(shared_from_this()));
	}
	return discipline;
}

MaxTempEstimator *Configuration::getMaxTempEstimatorFromFile()
{
	std::vector<std::string> str = getStringList("rlDiscipline", "maxTempEstimator");
	if (str.size() == 0)
		return nullptr;
	if (!str[0].compare(EnvelopeDetector::configKey))
	{
		double decayCoeff = getDoubleValue("rlDiscipline","peakDecaySpeed");
		return new EnvelopeDetector(decayCoeff);
	}
	if (!str[0].compare(SquareMaxTempEstimator::configKey))
		return new SquareMaxTempEstimator();
	if (!str[0].compare(MonomialMaxTempEstimator::configKey))
	{
		int order = 2;
		if (str.size() > 1)
			order = std::stoi(str[1]);
		return new MonomialMaxTempEstimator(order);
	}
	if (!str[0].compare(ExponentialMaxTempEstimator::configKey))
	{
		double scaling = 1.0;
		double offset = 0.0;
		if (str.size() > 1)
		{
			scaling = std::stod(str[1]);
			offset = std::stod(str[2]);
		}
		return new ExponentialMaxTempEstimator(scaling, offset);
	}
	return nullptr;
}



double Configuration::getTempLimit()
{
	double tempLimit = getDoubleValue("rlDiscipline", "tempLimit");
	return tempLimit;
}









