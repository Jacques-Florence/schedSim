/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "missedDeadline.h"

#include <cassert>
#include <iostream>
#include <iomanip>

#include <utils/log.h>
#include <scheduler/process.h>
#include <scheduler/taskScheduler.h>
#include <scheduler/system.h>
#include <scheduler/queue.h>

using namespace Scheduler;

void MissedDeadline::process()
{
	assert(task != nullptr);
	//std::cout << "deadline for process "<<task->getPid()<<"\n";
	/*If we can't find the job in the system, it has already successfully completed*/
	bool inSystem = false;
	std::shared_ptr<Process> running = System::getInstance()->getProc()->getRunningTask();
	if (running != nullptr
		&& running->getPid() == task->getPid()
		&& running->getJobNumber() == task->getJobNumber())
	{
		inSystem = true;
	}
	else
	{
		Queue *queue = Queue::getReadyQueue();
		for (auto it = queue->begin(); it != queue->end(); it++)
		//this is very bad performance. Can we do better?
		{
			if ((*it) == task
				&& ((*it)->getJobNumber() == task->getJobNumber()))
			{
				inSystem = true;
				break;
			}
		}
	}
	if (inSystem)
	{
		print();
		TaskScheduler *scheduler = System::getInstance()->getScheduler();
		scheduler->dealWithMissedDeadlines(task);
		scheduler->scheduleTask(eventType);
	}
	else
	{
		//std::cout << "Task "<<task->getPid()<<":"<<task->getJobNumber()<<" has completed successfully\n";
	}
}



std::string MissedDeadline::getName()
{
	assert(task != nullptr);
	return "process missed deadline";
}


void MissedDeadline::print()
{
#ifdef PRINT
	Utils::Log log;
	log << std::fixed << std::setfill(' ') << std::setw(7) << std::setprecision(3);
	log << getTime() << ": ";
	log << Utils::Log::Color::red << "process ";
	log << task->getPid()<<" missed deadline\n"<< Utils::Log::Color::normal;
#endif
}
