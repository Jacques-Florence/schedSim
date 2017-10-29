/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "newJob.h"

#include <atomic>
#include <cassert>
#include <thread>

#include <scheduler/process.h>
#include <scheduler/system.h>
#include <scheduler/taskScheduler.h>

#include "missedDeadline.h"

using namespace Scheduler;


std::atomic<bool> NewJob::startEventScheduling(false);
NewJob *NewJob::processBeingCreated(nullptr);

void NewJob::init()
{
	initEventSchedulingThread();
}

void NewJob::initEventSchedulingThread()
{
#if 0
	startEventScheduling = false;
	static std::thread nextEventSchedulingThread(eventSchedulingThreadFunction);
	processBeingCreated = nullptr;
	nextEventSchedulingThread.detach();
#endif
}

void NewJob::eventSchedulingThreadFunction()
{
	while (true)
	{
		while(!startEventScheduling)
			;
		processBeingCreated->scheduleNextEvent();
		startEventScheduling = false;
	}
}


void NewJob::process()
{
	assert(task != nullptr);
	if (task == nullptr) //this should not happen
		task = createTask();
	queueProcess(task);
	task->setDeadlineTimeFromStartTime(time);
	processBeingCreated = this;
	//startEventScheduling = true;
	print();
	System::getInstance()->getScheduler()->scheduleTask(eventType);
	processBeingCreated->scheduleNextEvent();
	//while (startEventScheduling)
	//	;
	return;
}

std::string NewJob::getName()
{
	return "New job";
}

/*This is not used normally*/
std::shared_ptr<Process> NewJob::createTask()
{
	double deadline = 30.0;
	std::shared_ptr<Process> p = Process::createRealTimeTask(10.0, 35.0, deadline,
		((pid != -1) ? pid:Process::getNewPid()));

	return p;
}

void NewJob::scheduleNextEvent()
{
	//std::cerr << "scheduling next event\n";
	if(renew)
	{
		std::shared_ptr<NewJob> e = std::make_shared<NewJob>(time + task->getPeriod(), true);
		std::shared_ptr<Process> newTask = Process::createNextJob(*task);
		assert(newTask != nullptr);
		e->setTask(newTask);
		EventList::getInstance()->insert(e);
	}

	/*also schedule the missed deadline event.*/
	scheduleMissedDeadlineEvent();
}

void NewJob::scheduleMissedDeadlineEvent()
{
	std::shared_ptr<MissedDeadline> d = std::make_shared<MissedDeadline>(task->getDeadlineTime());
	d->setTask(task);
	EventList::getInstance()->insert(d);
}


