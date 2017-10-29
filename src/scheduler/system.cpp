/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "system.h"

#include <cassert>
#include <memory>

#include <utils/log.h>
#include <utils/randomGenerator.h>

#include "process.h"
#include "processor.h"
#include "queue.h"
#include "schedulerConfiguration.h"
#include "taskScheduler.h"

using namespace Scheduler;

System *System::instance = nullptr;

System *System::getInstance()
{
	assert (instance != nullptr);
	return instance;
}

void System::buildSystem(std::shared_ptr<SchedulerConfiguration> c)
{
	Utils::RandomGenerator *processGen = new Utils::RandomGenerator;

	if (instance == nullptr)
	{
		instance = new System();
		instance->conf = c;
		instance->proc = new Processor(c);
		instance->proc->setTemperatureModel(c->getTemperatureModelFromFile());
		instance->governor = instance->conf->getFreqGovernorFromFile();
		assert(instance->governor != nullptr);
		Utils::Log log;
#ifdef PRINT
		log << Utils::Log::Color::green << "Using frequency governor ";
		log << instance->governor->getName() << Utils::Log::Color::normal << "\n";
#endif
		instance->reportsFolder = c->getStringValue("global", "reportsFolder");
	}
	else
	{
		instance->conf = c;
	}
	delete processGen;
}

System::System()
{
}

System::~System()
{
	delete proc;
	delete scheduler;
	delete governor;
}

void System::updateTemperature(double timeInterval)
{
	proc->updateTemperature(timeInterval);
}

Processor *System::getProc()
{
	return proc;
}


void System::printReports()
{
	proc->printReports(reportsFolder);
	governor->printReport(reportsFolder);
	printProcessesReport();
}

void System::printProcessesReport()
{
	for (size_t i = 0; i < staticTaskSet.size(); i++)
	{
		std::shared_ptr<Process> p = staticTaskSet[i];
		std::ofstream file;
		file.open((conf->getFilePrefix() + "processes.txt"), std::ios_base::app);
		p->print(file);
		file.close();
	}
}


void System::updateFreq()
{
	if (!proc->powered())
		return;
	Queue *queue = Queue::getReadyQueue();
	governor->updateFreq(proc, queue);
}

TaskScheduler *System::getScheduler()
{
	assert(conf != nullptr);
	if (scheduler == nullptr)
		scheduler = new TaskScheduler(conf);
	return scheduler;
}



void System::end()
{
	scheduler->end(reportsFolder);
	printReports();
}


void System::addRealTimeTask(std::shared_ptr<Process> p)
{
	staticTaskSet.push_back(p);
}


std::vector<std::shared_ptr<Process>> System::getStaticTaskSet()
{
	return staticTaskSet;
}


long long int System::getJobsArrivalCount()
{
	return jobsArrivalCount;
}

void System::incrementJobsArrivalCount()
{
	jobsArrivalCount++;
}




