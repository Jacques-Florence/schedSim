/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "terminates.h"


#include <cassert>
#include <scheduler/system.h>
#include <scheduler/taskScheduler.h>
#include <scheduler/process.h>
#include <scheduler/specialMailbox.h>
#include <scheduler/time.h>


using namespace Scheduler;


void Terminates::process()
{
	assert(task != nullptr);
	print();

	SpecialMailbox::getInstance()->put(Time::getTime(), task);
	TaskScheduler *scheduler = System::getInstance()->getScheduler();
	scheduler->clearRunningTask(task);
	scheduler->scheduleTask(eventType);
	return;
}

std::string Terminates::getName()
{
	return "Task terminates";
}


