/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */




#include "timeoutEvent.h"

#include "eventList.h"
#include "eventType.h"
#include <scheduler/process.h>
#include <scheduler/processor.h>
#include <scheduler/queue.h>
#include <scheduler/system.h>
#include <scheduler/taskScheduler.h>


using namespace Scheduler;

void TimeOut::process()
{
	std::shared_ptr<TimeOut> nextTimeout = getNextTimeout();
	if (renew)
	{
		nextTimeout->setInterval(interval);
		EventList::getInstance()->insert(nextTimeout);
	}
	print();
	doWork();
	return;
}
void TimeOut::doWork()
{
	System::getInstance()->getScheduler()->scheduleTask(eventType);
}


std::string SchedTimeOut::getName()
{
	return "Timeout";
}

std::shared_ptr<TimeOut> SchedTimeOut::getNextTimeout()
{
	return std::make_shared<SchedTimeOut>(time+interval);
}

double TimeOut::getInterval()
{
	return interval;
}

void TimeOut::setInterval(double inter)
{
	interval = inter;
}

void UsageUpdate::doWork()
{
	System::getInstance()->getProc()->updateUsage();
}

std::shared_ptr<TimeOut> UsageUpdate::getNextTimeout()
{
	return std::make_shared<UsageUpdate>(time + interval);
}

std::string UsageUpdate::getName()
{
	return "Usage update";
}

std::string StatsTick::getName()
{
	return "Stats tick";
}

std::shared_ptr<TimeOut> StatsTick::getNextTimeout()
{
	return std::make_shared<StatsTick>(time + interval);
}

void StatsTick::doWork()
{
	System::getInstance()->getProc()->updateTicks();
}

void FreqUpdate::doWork()
{
	System::getInstance()->updateFreq();
	return;
}

std::shared_ptr<TimeOut> FreqUpdate::getNextTimeout()
{
	return std::make_shared<FreqUpdate>(time+interval);
}

std::string FreqUpdate::getName()
{
	return "Frequency update";
}


void DummyEvent::doWork()
{
}

std::shared_ptr<TimeOut> DummyEvent::getNextTimeout()
{
	return std::make_shared<DummyEvent>(time+interval);
}

std::string DummyEvent::getName()
{
	return "Dummy event";
}
