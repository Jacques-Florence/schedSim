/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SCHEDULERCONFIGURATION_H
#define SCHEDULERCONFIGURATION_H

#include <memory>

#include <utils/configuration.h>

namespace Utils
{
	class RandomGenerator;
	class BoundedRandomDistribution;
}

namespace Scheduler
{

class FreqGovernor;
class SchedulingDiscipline;
class TemperatureModel;

class SchedulerConfiguration : public Utils::Configuration
{
public:
	SchedulerConfiguration(std::string filename) : Configuration(filename){};
	virtual FreqGovernor *getFreqGovernorFromFile();
	virtual std::unique_ptr<SchedulingDiscipline> getDisciplineFromFile();
	virtual TemperatureModel *getTemperatureModelFromFile();
	virtual double getRunningTime();
	virtual std::shared_ptr<Utils::BoundedRandomDistribution>
		getDistributionFromFile(Utils::RandomGenerator *gen);
private:
};


}


#endif
