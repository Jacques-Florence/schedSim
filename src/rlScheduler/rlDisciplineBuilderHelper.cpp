/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlDisciplineBuilderHelper.h"

#include <cassert>

#include <utils/math.h>

#include <mdp/builder.h>
#include <mdp/mdpModel.h>
#include <mdp/actionDimension.h>

#include <scheduler/system.h>
#include <scheduler/process.h>
#include <scheduler/queue.h>

#include "actions.h"
#include "configuration.h"
#include "domainModel.h"
#include "stateDimensions/taskDimensions.h"
#include "stateDimensions/timeDimension.h"
#include "stateDimensions/temperatureDimension.h"

using namespace RlScheduler;







void RlDisciplineBuilderHelper::addActions(Mdp::Builder *builder)
{
#define ACTION_DIMS 0 //FIXME: not working because of the do-while loop... the dynamic cast fails...
#if ACTION_DIMS
	Mdp::ActionDimension *processDimension = new Mdp::ActionDimension;
#endif
	for (size_t i = 0; i < getNbOfTasks(); i++)
	{
#if ACTION_DIMS
		processDimension->addAction(new Action(i));
#else
		builder->addAction(new Action(i));
#endif
	}
#if ACTION_DIMS
	processDimension->addAction(new SleepAction());
	builder->addActionDimension(processDimension);
#else
	builder->addAction(new SleepAction());
#endif
}



void RlDisciplineBuilderHelper::addStates(Mdp::Builder *builder, std::shared_ptr<Configuration> conf)
{
	addTaskStates(builder);
	addTimeStates(builder, conf);
	addTemperatureStates(builder, conf);
}

void RlDisciplineBuilderHelper::addTemperatureStates(Mdp::Builder *builder, std::shared_ptr<Configuration> conf)
{
	if (useTemperatureStates(conf))
	{
		int nbOfPos = conf->getIntValue("rlDiscipline", "nbTemperatureStates");
		builder->addDimension(new TemperatureDimension(nbOfPos));
	}
}
bool RlDisciplineBuilderHelper::useTemperatureStates(std::shared_ptr<Configuration> conf)
{
	return conf->getBoolValue("rlDiscipline", "temperatureState", false);
}

void RlDisciplineBuilderHelper::addTimeStates(Mdp::Builder *builder, std::shared_ptr<Configuration> conf)
{
	if (!useTimeStates(conf))
		return;
	int nbTimeZones = 0;
	std::vector<std::shared_ptr<Scheduler::Process>>
		processes = Scheduler::System::getInstance()->getStaticTaskSet();
	assert(processes.size() > 0);
	double hyperperiod = (double) lcm(processes);
	for (size_t i = 0; i < processes.size(); i++)
	{
		nbTimeZones += hyperperiod/processes[i]->getPeriod();
	}
	builder->addDimension(new TimeDimension(nbTimeZones));
}


bool RlDisciplineBuilderHelper::useTimeStates(std::shared_ptr<Configuration> conf)
{
	return conf->getBoolValue("rlDiscipline","timeState", false);
}

void RlDisciplineBuilderHelper::addTaskStates(Mdp::Builder *builder)
{
	for (size_t i = 0; i < getNbOfTasks(); i++)
	{
		builder->addDimension(new TaskDimension(i));
	}
}

size_t RlDisciplineBuilderHelper::getNbOfTasks()
{
	return Scheduler::System::getInstance()->getStaticTaskSet().size();
}



double RlDisciplineBuilderHelper::lcm(std::vector<std::shared_ptr<Scheduler::Process>> processes)
{

	static const double eps = 0.000001;
	std::vector<int> array(processes.size());
	for (size_t i = 0; i < processes.size(); i++)
	{
		assert(processes[i]->getPeriod() <= floor(processes[i]->getPeriod()) + eps);
		array[i] = (int) floor(processes[i]->getPeriod());
	}
	return Utils::lcm(array);

	return 0.0;
}



















