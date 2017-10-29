/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "taskSetGenerator.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include <utils/distributions/boundedRandomDistribution.h>
#include <utils/distributions/bernoulli.h>

#include "freqConstants.h"
#include "process.h"
#include "schedulerConfiguration.h"
#include "schedulingSimulator.h"


using namespace Scheduler;



void TaskSetGenerator::generate(
	  SchedulingSimulator *simulator
	, unsigned int nbOfTasks
	, double utilization
	, time_t seed
	, bool critical
	, bool integerPeriod
	, std::shared_ptr<Utils::BoundedRandomDistribution> dist
	)
{
	if (nbOfTasks <= 0)
		throw std::runtime_error("need to specify a number of tasks greater or equal than one");
	Utils::RandomGenerator gen;
	gen.seed(seed);

	std::vector<double> portion = generateCpuUtilizationOfTasks(nbOfTasks, &gen,
		utilization);
	std::vector<double> periods = generateTaskPeriods(nbOfTasks, integerPeriod, &gen);
	std::vector<double> aow = computeAow(periods, portion, nbOfTasks);

	for (size_t i = 0; i < periods.size(); i++)
	{
		std::cerr << "period: "<< periods[i] <<"\n";
		std::cerr << "aow: "<< aow[i] <<"\n";
		std::cerr << "portion: "<< portion[i] <<"\n";
	}

	bool enablePriority = arePrioritiesEnabled(simulator->conf);
	generateTasks(
		  periods
		, aow
		, &gen
		, enablePriority
		, nbOfTasks
		, critical
		, simulator
		, dist
		);

}

void TaskSetGenerator::generateTasks(
	  std::vector<double> periods
	, std::vector<double> aow
	, Utils::RandomGenerator *gen
	, bool enablePriority
	, unsigned int nbOfTasks
	, bool critical
	, SchedulingSimulator *simulator
	, std::shared_ptr<Utils::BoundedRandomDistribution> dist
	)
{
	int priority = 0;

	std::shared_ptr<Process> task;
	for (unsigned int i = 0; i < nbOfTasks; i++)
	{
		if (enablePriority)
		{
			priority = exp(20*i);
		}
		double startTime = 0.1;
		if (!critical)
		{
			startTime += gen->drawUniform(0.0, periods[i]);
		}
		std::cerr << "in the generator, aow is "<< aow[i] <<"\n";
		task = simulator->createRealTimeTask(startTime, periods[i], aow[i],
			0.0, priority, aow[i]/2.0);
		double powerSpan = simulator->conf->getDoubleValue("taskSet", "powerSpan");
		task->setPowerCoeff(1.0 + powerSpan*((double) i)
			/ ((double) nbOfTasks - 1.0));
		/*
		task->setDurationDistribution(nullptr);
		task->setDurationDistribution(std::make_shared<Utils::Bernoulli>(
			new Utils::RandomGenerator(0), 1.0));
		*/	
		task->setDurationDistribution(dist);
	}
}

std::vector<double> TaskSetGenerator::generateCpuUtilizationOfTasks(
	  unsigned int nbOfTasks
	, Utils::RandomGenerator *gen
	, double utilization
	)
{

	/*Let's determine the cpu utilization due to each of the tasks.
	Imagine a segment going from 0.0 to utilization.
	put nbOfTasks-1 dots on it.
	You have now partitioned the segment into nbOfTask subsegments.
	The length of each of those subsegments is the cpu utilization
	due to each of the corresponding task.*/
	std::vector<double> portion(nbOfTasks);
	std::vector<double> dots(nbOfTasks+1);
	dots[0] = 0.0;
	dots[nbOfTasks] = utilization;
	for (unsigned int i = 0; i < nbOfTasks-1; i++)
	{
		dots[i+1] = gen->drawUniform(0.0, utilization);
	}
	std::sort(dots.begin(), dots.end());
	for (unsigned int i = 0; i < nbOfTasks; i++)
	{
		portion[i] = dots[i+1] - dots[i];
	}

	return portion;
}



std::vector<double> TaskSetGenerator::computeAow(
	  std::vector<double> periods
	, std::vector<double> portion
	, unsigned int nbOfTask
	)
{
	std::vector<double> aow(nbOfTask);
	for (unsigned int i = 0; i < nbOfTask; i++)
	{
		/*this is not exactly minfreq, but the actual running frequency.
		it is equal to minfreq if we use the minfreq governor*/
		aow[i] = periods[i]*portion[i]*MINFREQ;
	}
	return aow;
}

bool TaskSetGenerator::arePrioritiesEnabled(std::shared_ptr<SchedulerConfiguration> conf)
{
	assert(conf != nullptr);
	std::string str = conf->getStringValue("taskSet", "priorities");
	if (!str.compare("yes"))
		return true;
	return false;
}



std::vector<double> TaskSetGenerator::generateTaskPeriods(
	  unsigned int nbOfTasks
	, bool integerPeriod
	, Utils::RandomGenerator *gen)
{
	std::vector<double> periods(nbOfTasks);
	for (unsigned int i = 0; i < nbOfTasks; i++)
	{
		periods[i] = gen->drawUniform(minT, maxT);
		if (integerPeriod == true)
		{
			periods[i] = (periods[i] < 1.0) ? 1.0 : round(periods[i]);
		}
	}
	return periods;
}









