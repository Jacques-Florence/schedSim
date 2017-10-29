/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "fcfsDiscipline.h"

#include <cassert>
#include <iostream>

#include <scheduler/queue.h>

using namespace Scheduler;

std::shared_ptr<Process> FcfsDiscipline::selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int)
{
	if (readyQueue->isEmpty())
	{
		assert(running == nullptr);
		return running; /*For a fcfs, this should be nullptr*/
	}
	return (*readyQueue->begin());
}


std::string FcfsDiscipline::getName()
{
	return "FCFS";
}

bool FcfsDiscipline::preempts(TriggeringEvent /*trigger*/)
{
	return false;
}
