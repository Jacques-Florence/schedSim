/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "newInteractiveProcess.h"

#include <fstream>

#include <utils/randomGenerator.h>

#include <scheduler/system.h>
#include <scheduler/process.h>
#include <scheduler/taskScheduler.h>

#include "eventList.h"

using namespace Scheduler;


void NewInteractiveProcess::process()
{
	task = createTask();
	std::ofstream file;
	file.open("processes.txt", std::ios_base::app);
	task->print(file);
	file.close();
	queueProcess(task);	
	scheduleNextEvent();
	print();
	System::getInstance()->getScheduler()->scheduleTask(eventType);
	return;
}

std::string NewInteractiveProcess::getName()
{
	return "New interactive process";
}

std::shared_ptr<Process> NewInteractiveProcess::createTask()
{
	double cpuLambda = 1.0/5.0;
	double ioLambda = 1.0/10.0;
	return Process::createProcess(cpuLambda, ioLambda);
}


void NewInteractiveProcess::scheduleNextEvent()
{
	if (!renew)
		return;
	EventList *list = EventList::getInstance();
	//The mean duration of a process is nbBursts*(5+10) = 150.
	double lambda = 1.0/150.0;
	double interval;
	do
	{
		interval = list->getRandomGenerator()->drawExp(lambda);
	} while(interval >= std::numeric_limits<double>::infinity());
	std::shared_ptr<Event> e = std::make_shared<NewInteractiveProcess>(time+interval, false);
	list->insert(e);
}



