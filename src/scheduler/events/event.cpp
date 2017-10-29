/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "coreEvents.h"

#include <fstream>
#include <iomanip>
#include <iostream>


#include "eventList.h"
#include "eventType.h"
#include <scheduler/process.h>

using namespace Scheduler;

Event::Event(double t, bool r) : time(t), renew(r)
{
}

Event::~Event()
{
}

void Event::setTask(std::shared_ptr<Process> p)
{
	task = p;
}

double Event::getTime()
{
	return time;
}

void Event::print()
{
#ifdef PRINT
	if (eventType == nothing)
		return;
	std::cout << std::fixed << std::setfill(' ') << std::setw(7) << std::setprecision(3)<< getTime() <<": ";
	if (task != nullptr)
	{
		std::cout << " Task"<<std::setfill(' ') << std::setw(3) << task->getPid();
		if (task->isRealTime())
		{
			std::cout << ":"<<task->getJobNumber();
		}
		std::cout << ": ";
	}
	std::cout << getName()<<"\n";
#endif
}

