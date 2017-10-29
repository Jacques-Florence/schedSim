/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "taskScheduler.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include <utils/log.h>
#include "events/coreEvents.h"
#include "events/eventList.h"
#include "events/eventType.h"
#include "process.h"
#include "queue.h"
#include "schedulerConfiguration.h"
#include "discipline/schedulingDiscipline.h"
#include "system.h"
#include "time.h"

#include "specialMailbox.h"

#define PRINT 1

using namespace Scheduler;

TaskScheduler::TaskScheduler(std::shared_ptr<SchedulerConfiguration> c) : deadlinesHistory(Utils::Record(c, "deadlineMisses")), conf(c)
{
	setDiscipline(conf->getDisciplineFromFile());
}


TaskScheduler::~TaskScheduler()
{
}

void TaskScheduler::scheduleTask(TriggeringEvent trigger)
{
	//printStatus();
	Utils::Log log;
	static Queue *readyQueue = Queue::getReadyQueue();
	static Processor *proc = System::getInstance()->getProc();
	
	printInvocation();


	if (trigger == TriggeringEvent::terminate)
	{
	}	
	else
	{
		SpecialMailbox::getInstance()->invalidate();
	}


	if (trigger == TriggeringEvent::newprocess)
	{
		System::getInstance()->incrementJobsArrivalCount();
	}

	if (!discipline->preempts(trigger) && proc->isBusy())
	{
		/*The event that triggered the scheduler invocation does not preempt
		this particular discipline used*/
		return;
	}

	std::shared_ptr<Process> nextTask = discipline->selectNextTask(readyQueue,
		proc->getRunningTask(), deadlineMisses);
	
	if (proc->isRunning(nextTask))
		return;
	
	if (discipline->preempts(trigger)) 
		putRunningTaskBackToReadyQueue(proc->getRunningTask());
	if (!proc->powered()) /*Just to be sure.
	This should not happen normally.*/
		return;
	proc->setRunning(nextTask);

	if (nextTask != nullptr)
	{
		readyQueue->remove(nextTask);
		scheduleEndOfBurst(nextTask);
	}

	printRunningProcess(nextTask);
	return;
}

void TaskScheduler::dealWithMissedDeadlines(std::shared_ptr<Process> p)
{
#if 0
	deadlineMisses++;
#else
	deadlineMisses += (p->getPriority()+1);//TODO decide according to some configuration option
#endif
	static Processor *proc = System::getInstance()->getProc();
	std::shared_ptr<Process> running = proc->getRunningTask();
	deadlinesHistory.add(Time::getTime(), p->getPid());
	if (running == p)
	{
		std::shared_ptr<Event> ev = getBurstEnd();
		EventList::getInstance()->remove(ev);
		proc->setRunning(nullptr);
		return;
	}
	if (Queue::getReadyQueue()->remove(p) != nullptr)
	{
	}
}


void TaskScheduler::clearRunningTask(std::shared_ptr<Process> p)
{
	static Processor *proc = System::getInstance()->getProc();
	assert(p == proc->getRunningTask());
	proc->setRunning(nullptr);
	printRunningProcess(nullptr);
}

void TaskScheduler::scheduleEndOfBurst(std::shared_ptr<Process> runningTask)
{
	static Processor *proc = System::getInstance()->getProc();
	static EventList *eventList = EventList::getInstance();
	if (!proc->isBusy())
		return;

	double newTime = Time::getTime() + runningTask->getCurrentCpuAow()/proc->getFreq();
	bool wait = runningTask->advanceBurst();
	std::shared_ptr<Event> e;
	if (wait)
	{
		e = std::make_shared<Waiting>(newTime);
	}
	else
	{
		e = std::make_shared<Terminates>(newTime);
	}
	e->setTask(runningTask);

	setBurstEnd(eventList->insert(e));
}

void TaskScheduler::putRunningTaskBackToReadyQueue(std::shared_ptr<Process> runningTask)
{
	static Processor *proc = System::getInstance()->getProc();
	static EventList *eventList = EventList::getInstance();
	static Queue *readyQueue = Queue::getReadyQueue();
	if (!proc->isBusy())
		return;
	std::shared_ptr<Event> ev = getBurstEnd();
	if (ev != nullptr)
	{
		double newAow = (ev->getTime() - Time::getTime())*proc->getFreq();
		runningTask->updateCurrentAow(newAow);
		eventList->remove(ev);
		readyQueue->add(runningTask);
	}
}


void TaskScheduler::setBurstEnd(std::shared_ptr<Event> e)
{
	burstEnd = e;
}

std::shared_ptr<Event> TaskScheduler::getBurstEnd()
{
	return burstEnd;
}




void TaskScheduler::printInvocation()
{
#ifdef PRINT
	Utils::Log log;
	log << Utils::Log::Color::lightBlue;
	log << "    Scheduler invoked. Ready queue contains ";
	log << Queue::getReadyQueue()->getDisplay() << Utils::Log::Color::normal <<"\n";
#endif
}

void TaskScheduler::printRunningProcess(std::shared_ptr<Process> /*runningTask*/)
{
#ifdef PRINT
	Utils::Log log;
	if (runningTask != nullptr)
	{
		log << Utils::Log::Color::blue;
		log <<"    Currently running process number "<<runningTask->getPid();
		
		if (runningTask->isRealTime())
			log << ":"<< runningTask->getJobNumber();
	
		log << Utils::Log::Color::normal << "\n";
	}
	else
	{
		log << Utils::Log::Color::blue;
		log << "    Processor sleeping" << Utils::Log::Color::normal << "\n";
	}
#endif
}





void TaskScheduler::setDiscipline(std::unique_ptr<SchedulingDiscipline> disc)
{
	discipline = std::move(disc);
	assert(discipline != nullptr);
#ifdef PRINT
	Utils::Log log;
	log << Utils::Log::Color::green << "Using scheduling discipline ";
	log << discipline->getName() << Utils::Log::Color::normal << "\n";
#endif
}





void TaskScheduler::printReports(std::string folder)
{
	printDeadlineMissesReport(folder);
}


void TaskScheduler::printDeadlineMissesReport(std::string folder)
{
	deadlinesHistory.printToFile(folder);
}



void TaskScheduler::printStatus()
{
	EventList::getInstance()->print();
	Queue::getReadyQueue()->print();
	Queue::getWaitQueue()->print();
}


void TaskScheduler::end(std::string folder)
{
	discipline->end();
	printReports(folder);
}


