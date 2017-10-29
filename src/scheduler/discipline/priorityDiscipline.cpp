/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "priorityDiscipline.h"

#include <algorithm>
#include <vector>

#include <scheduler/process.h>
#include <scheduler/queue.h>

using namespace Scheduler;


std::shared_ptr<Process> PriorityDiscipline::selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int)
{
	updatePriorities(readyQueue, running);

	int highestPriority = std::numeric_limits<int>::min();
	std::shared_ptr<Process> candidate = running;
	if (running != nullptr)
		highestPriority = candidate->getPriority();
	for (auto it = readyQueue->begin() ; it != readyQueue->end(); it++)
	{
		if ((*it)->getPriority() > highestPriority)
		{
			candidate = (*it);
			highestPriority = candidate->getPriority();
		}
	}
	return candidate;
}

bool PriorityDiscipline::preempts(TriggeringEvent trigger)
{
	return (trigger == newprocess || trigger == ready);
}


void PriorityDiscipline::updatePriorities(Queue * readyQueue, std::shared_ptr<Process>  running)
{
	std::vector<std::shared_ptr<Process> > ranking(readyQueue->size());
	unsigned int i = 0;
	for (auto it = readyQueue->begin(); it != readyQueue->end(); it++, i++)
	{
		ranking[i] = (*it);
	}
	if (running != nullptr)
		ranking.push_back(running);
	std::sort(ranking.begin(), ranking.end(), getComparator());
	for (unsigned int i = 0; i < ranking.size(); i++)
		ranking[i]->setPriority(ranking.size()-i);
	
}

PriorityDiscipline::ComparatorPointer PriorityDiscipline::getComparator()
{
	return [](std::shared_ptr<Process> a, std::shared_ptr<Process> b){return a->getPriority() > b->getPriority();};
}





