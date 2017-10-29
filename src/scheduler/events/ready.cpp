/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "ready.h"

#include <cassert>

#include <scheduler/system.h>
#include <scheduler/queue.h>
#include <scheduler/taskScheduler.h>
#include <scheduler/process.h>

using namespace Scheduler;


void Ready::process()
{
	assert(task != nullptr);
	Queue::getReadyQueue()->add(task);
	Queue::getWaitQueue()->remove(task);
	print();
	System::getInstance()->getScheduler()->scheduleTask(eventType);
	return;
}

std::string Ready::getName()
{
	return "Task ready";
}




