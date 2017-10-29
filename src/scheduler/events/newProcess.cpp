/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "newProcess.h"

#include <scheduler/queue.h>

using namespace Scheduler;


NewProcess::~NewProcess()
{
}

void NewProcess::queueProcess(std::shared_ptr<Process> task)
{
	Queue::getReadyQueue()->add(task);
}
