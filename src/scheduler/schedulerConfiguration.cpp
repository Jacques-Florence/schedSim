/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "schedulerConfiguration.h"

#include <utils/randomGenerator.h>
#include <utils/distributions/uniformDistribution.h>
#include <utils/distributions/diracOneDistribution.h>
#include <utils/distributions/bernoulli.h>

#include "governor/maxGovernor.h"
#include "governor/minGovernor.h"
#include "governor/conservativeGovernor.h"

#include "discipline/edfDiscipline.h"
#include "discipline/fcfsDiscipline.h"
#include "discipline/fixedPriorityDiscipline.h"
#include "discipline/rmsDiscipline.h"
#include "discipline/roundRobinDiscipline.h"

#include "temperatureModel/simpleTemperatureModel.h"
#include "temperatureModel/temperatureAndAgingModel.h"

using namespace Scheduler;

FreqGovernor *SchedulerConfiguration::getFreqGovernorFromFile()
{
	std::string value = getStringValue("scheduler", "governor");
	if (!value.compare(MinGovernor::configKey))
		return (new MinGovernor);
	if (!value.compare(MaxGovernor::configKey))
		return (new MaxGovernor);
	if (!value.compare(ConservativeGovernor::configKey))
		return (new ConservativeGovernor);
	return nullptr; 
}


std::unique_ptr<SchedulingDiscipline> SchedulerConfiguration::getDisciplineFromFile()
{
	std::unique_ptr<SchedulingDiscipline> disc{nullptr};
	std::string value = getStringValue("scheduler", "discipline");
	if (!value.compare(EdfDiscipline::configKey))
		disc = std::make_unique<EdfDiscipline>(std::dynamic_pointer_cast<SchedulerConfiguration>(shared_from_this()));
	if (!value.compare(FcfsDiscipline::configKey))
		disc = std::make_unique<FcfsDiscipline>(std::dynamic_pointer_cast<SchedulerConfiguration>(shared_from_this()));
	if (!value.compare(FixedPriorityDiscipline::configKey))
		disc = std::make_unique<FixedPriorityDiscipline>(std::dynamic_pointer_cast<SchedulerConfiguration>(shared_from_this()));
	if (!value.compare(RmsDiscipline::configKey))
		disc = std::make_unique<RmsDiscipline>(std::dynamic_pointer_cast<SchedulerConfiguration>(shared_from_this()));
	if (!value.compare(RoundRobinDiscipline::configKey))
		disc = std::make_unique<RoundRobinDiscipline>(std::dynamic_pointer_cast<SchedulerConfiguration>(shared_from_this()));
	return std::move(disc);
}




TemperatureModel *SchedulerConfiguration::getTemperatureModelFromFile()
{
	std::string value = getStringValue("scheduler", "temperatureModel");
	if (!value.compare(SimpleTemperatureModel::configKey))
		return (new SimpleTemperatureModel(shared_from_this()));
	if (!value.compare(TemperatureAndAgingModel::configKey))
		return (new TemperatureAndAgingModel(shared_from_this()));
	return nullptr;
}


double SchedulerConfiguration::getRunningTime()
{
	return getDoubleValue("scheduler", "runningTime");
}


std::shared_ptr<Utils::BoundedRandomDistribution>
SchedulerConfiguration::getDistributionFromFile(Utils::RandomGenerator *gen)
{
	std::string value = getStringValue("scheduler", "distribution");
	std::shared_ptr<Utils::BoundedRandomDistribution> ret = nullptr;
	if (!value.compare("uniform"))
	{
		ret = std::make_shared<Utils::UniformDistribution>(gen);
	}
	if (!value.compare("none") || !value.compare("deterministic"))
	{
		ret = std::make_shared<Utils::DiracOneDistribution>(gen);
	}
	if (!value.substr(0, 9).compare("bernoulli"))
	{
		double p = std::stod(value.substr(9, std::string::npos));
		ret = std::make_shared<Utils::Bernoulli>(gen, p);
	}
	return ret;
}




