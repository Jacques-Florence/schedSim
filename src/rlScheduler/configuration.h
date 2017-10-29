/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_SCHEDULER_CONFIGURATION_H
#define RL_SCHEDULER_CONFIGURATION_H

#include <scheduler/schedulerConfiguration.h>


namespace Scheduler
{
	class SchedulingDiscipline;
	class TemperatureModel;
}


namespace RlScheduler
{

class MaxTempEstimator;

class Configuration : public Scheduler::SchedulerConfiguration
{
public:
	Configuration(std::string str) : Scheduler::SchedulerConfiguration(str){};
	virtual std::unique_ptr<Scheduler::SchedulingDiscipline> getDisciplineFromFile();
	MaxTempEstimator *getMaxTempEstimatorFromFile();
	double getTempLimit();
};


}
#endif
