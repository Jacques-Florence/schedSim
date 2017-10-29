/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "waiting.h"

#include <cassert>

#include <scheduler/queue.h>
#include <scheduler/process.h>
#include <scheduler/taskScheduler.h>
#include <scheduler/system.h>

#include "ready.h"

using namespace Scheduler;


void Waiting::process()
{
	assert(task != nullptr);
	Queue::getWaitQueue()->add(task);
	print();
	std::shared_ptr<Event> e = std::make_shared<Ready>(time + task->getCurrentIoTime());
	e->setTask(task);
	EventList::getInstance()->insert(e);
	TaskScheduler *scheduler = System::getInstance()->getScheduler();
	scheduler->clearRunningTask(task);
	scheduler->scheduleTask(eventType);
	return;
}

std::string Waiting::getName()
{
	return "Task waiting";
}

