/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "roundRobinDiscipline.h"

#include <cassert>
#include <iostream>


#include <scheduler/queue.h>

using namespace Scheduler;


std::shared_ptr<Process> RoundRobinDiscipline::selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int)
{
	if (readyQueue->isEmpty())
	{
		return running;
	}
	return (*readyQueue->begin());
}



std::string RoundRobinDiscipline::getName()
{
	return "Round Robin";
}


bool RoundRobinDiscipline::preempts(TriggeringEvent trigger)
{
	return trigger == schedTimeOut;
}




