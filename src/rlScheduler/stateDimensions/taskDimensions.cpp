/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "taskDimensions.h"

#include <scheduler/queue.h>
#include <scheduler/process.h>

#include <rlScheduler/domainModel.h>

using namespace RlScheduler;

TaskDimension::TaskDimension(int id) : pid(id)
{
}


std::string TaskDimension::getName()
{
	return ("dimension for process " + pid);
}

Mdp::statePosition_t TaskDimension::getPosition()
{
	if (model == nullptr)
		model = getModel<DomainModel>();

	static Scheduler::Queue *queue = model->readyQueue;
	if ((model->running != nullptr) && model->running->getPid() == pid)
		return 2;
	for (auto i = queue->begin(); i != queue->end(); i++)
	{
		if ((*i)->getPid() == pid)
			return 1;
	}
	return 0;
}

size_t TaskDimension::getNumberOfPositions()
{
	return 3; /*each process can be either running, in the ready queue or in the wait queue*/
}

