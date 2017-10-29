/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "schedulingSimulator.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>

#include <utils/log.h>
#include <utils/randomGenerator.h>

#include "events/coreEvents.h"
#include "events/eventList.h"
#include "freqConstants.h"
#include "process.h"
#include "schedulerConfiguration.h"
#include "system.h"
#include "taskSetGenerator.h"
#include "time.h"
#include "xmlTaskSet.h"

using namespace Scheduler;

SchedulingSimulator::SchedulingSimulator()
{
	conf = std::make_shared<SchedulerConfiguration>("configuration.conf");
	System::buildSystem(conf);
}

SchedulingSimulator::SchedulingSimulator(std::shared_ptr<SchedulerConfiguration> c) : conf(c)
{
	NewJob::init();
	System::buildSystem(c);
}

SchedulingSimulator::~SchedulingSimulator()
{
	Process::end();
}

void SchedulingSimulator::initializeTaskSet()
{
	std::string value = conf->getStringValue("taskSet", "tasksetSource");
	if (!value.compare("xml"))
		initializeTaskSetFromXml();
	else if (!value.compare("random"))
		initializeTaskSetRandomly();
	else if (!value.compare("compiled"))
		initializeTaskSetAtCompileTime();
	else initializeTaskSetAtCompileTime();
}

void SchedulingSimulator::initializeTaskSetFromXml()
{
	XmlTaskSet xml;
	std::shared_ptr<std::vector<std::shared_ptr<Process>>>
		taskset = xml.getRealTimeTaskSetFromXml("xml/taskset.xml");
	for (size_t i = 0; i < taskset->size(); i++)
	{
		System::getInstance()->addRealTimeTask((*taskset)[i]);
		double startTime = 0.1; //TODO HARDCODED !!!
		std::shared_ptr<Event> rt = std::make_shared<NewJob>(startTime);
		rt->setTask((*taskset)[i]);
		EventList::getInstance()->insert(rt);
		//std::cerr << "added real-time task. The event list is:\n";
		//EventList::getInstance()->print();
	}
}

void SchedulingSimulator::initializeTaskSetRandomly()
{
	int nbOfTasks = conf->getIntValue("taskSet","nbOfTasks");
	double utilization = conf->getDoubleValue("taskSet", "utilization");
	time_t tasksetSeed = conf->getIntValue("taskSet","seed");
	std::shared_ptr<Utils::BoundedRandomDistribution> dist;
	dist = conf->getDistributionFromFile(&randomGenerator);
	TaskSetGenerator::generate(this, nbOfTasks, utilization,
		tasksetSeed, true, true, dist);
}

void SchedulingSimulator::initializeTaskSetAtCompileTime()
{
#if 0
	/*Utilization for this task set is 0.792*/
	createRealTimeTask(0.1, 35.0, 10.0*100, 25.0);
	createRealTimeTask(0.1, 25.0, 6.0*100, 6.0);
	createRealTimeTask(0.1, 15.0, 4.0*100, 14.9);
#endif
#if 0
	/*Utilization for this task set is 0.972*/
	createRealTimeTask(0.1, 35.0, 10.0*100);
	createRealTimeTask(0.1, 25.0, 8.0*100);
	createRealTimeTask(0.1, 15.0, 3.0*100);
	createRealTimeTask(0.1, 30.0, 5.0*100);
#endif	
#if 0
	/*Utilization for this task set is 0.967*/
	createRealTimeTask(0.1, 30.0, 6.0*100);
	createRealTimeTask(0.1, 20.0, 8.0*100);
	createRealTimeTask(0.1, 15.0, 3.0*100);
	createRealTimeTask(0.1, 30.0, 5.0*100);
#endif	
	//simulator.createRealTimeTask(0.0, 15.0, 7.0, 15.0);
#if 0
	createInteractiveProcess(1.0);
	createInteractiveProcess(1.0);
	createInteractiveProcess(10.0);
	createInteractiveProcess(100.0);
	createInteractiveProcess(300.0);
#endif

#if 1
	createRealTimeTask(0.1, 200, 6000, 200, 2, 6000, 1.5);
	createRealTimeTask(0.1, 100, 3000, 200, 1, 3000, 1.0);
#endif

#if 0
	createRealTimeTask(0.1, 30.0, 5.0*100.0, 20.0, 0, 499.0, 1.0);
	createRealTimeTask(0.1, 20.0, 5.0*100.0, 20.0, 0, 499.0, 1.5);
#endif
}


std::shared_ptr<Process> SchedulingSimulator::createRealTimeTask(double startTime,
	double period, double wcet, double deadline, int priority, double bcet,
	double powerCoeff)
{
	if (deadline <= 0.0)
		deadline = period;
	std::shared_ptr<Process> p = Process::createRealTimeTask(wcet, period, deadline,
		Process::getNewPid(), priority, bcet);
	p->setPowerCoeff(powerCoeff);
	std::shared_ptr<Event> rt = std::make_shared<NewJob>(startTime);
	rt->setTask(p);
	EventList::getInstance()->insert(rt);
	System::getInstance()->addRealTimeTask(p);
	return p;
}

void SchedulingSimulator::createInteractiveProcess(double startTime)
{
	EventList::getInstance()->insert(std::make_shared<NewInteractiveProcess>(startTime));
}

void SchedulingSimulator::seedRandomGenerator(time_t seed)
{
	randomGenerator.seed(seed);
}



void SchedulingSimulator::endSimulation(double time)
{
	EventList *eventList = EventList::getInstance();;
	std::shared_ptr<Event> stopEvent = std::make_shared<StopSimulation>(time);
	eventList->insert(stopEvent);
}

void SchedulingSimulator::setUsageCalculationTimeout(double start, double interval)
{
	std::shared_ptr<UsageUpdate> cpuUsageUpdate = std::make_shared<UsageUpdate>(start);
	cpuUsageUpdate->setInterval(interval);
	EventList::getInstance()->insert(cpuUsageUpdate);
}

void SchedulingSimulator::setStatsTick(double start, double interval)
{
	std::shared_ptr<StatsTick> tick = std::make_shared<StatsTick>(start);
	tick->setInterval(interval);
	EventList::getInstance()->insert(tick);
}

void SchedulingSimulator::setFreqUpdate(double start, double interval)
{
	std::shared_ptr<FreqUpdate> freqTO = std::make_shared<FreqUpdate>(start);
	freqTO->setInterval(interval);
	EventList::getInstance()->insert(freqTO);
}

void SchedulingSimulator::setSchedulerTimeout(double start, double interval)
{
	std::shared_ptr<SchedTimeOut> timeout = std::make_shared<SchedTimeOut>(start);
	timeout->setInterval(interval);
	EventList::getInstance()->insert(timeout);
}


void SchedulingSimulator::setDummyEvent(double start, double interval)
{
	std::shared_ptr<DummyEvent> dummy = std::make_shared<DummyEvent>(start);
	dummy->setInterval(interval);
	EventList::getInstance()->insert(dummy);
}


void SchedulingSimulator::startScheduler()
{
	EventList *list = EventList::getInstance();
	//std::cerr << "list of events:\n";
	//list->print();
	list->setRandomGenerator(&randomGenerator);
	Process::setRandomGenerator(&randomGenerator);
	while(!list->isEmpty())
	{
		std::shared_ptr<Event> e = list->getHead();
		Utils::Log log;
		Time::updateTime(e->getTime());
		double timeInterval = e->getTime() - previousTime;
		previousTime = e->getTime();
		System::getInstance()->updateTemperature(timeInterval);
		e->process();
		list->pop();
		
		static double previousTimeTrack = 0.0;
		double timeTrack = e->getTime();
		
		if (timeTrack - previousTimeTrack > 100000.0)
		{
			std::cerr << "time: "<< timeTrack <<"\n";
			previousTimeTrack = timeTrack;
		}
	}
	std::cerr << "after the startScheduler\n";
}


void SchedulingSimulator::turnOnProcessor(double start)
{
	Utils::Log log;
	std::shared_ptr<StartProc> startProc = std::make_shared<StartProc>(start);
	EventList::getInstance()->insert(startProc);
}













