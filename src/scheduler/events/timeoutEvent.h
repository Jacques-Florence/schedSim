/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TIMEOUTEVENT_H
#define TIMEOUTEVENT_H

#include "event.h"
#include "eventType.h"

namespace Scheduler
{

class TimeOut : public Event
{
public:
	TimeOut(double time, bool renew=true) : Event(time, renew){};
	void process() override;
	virtual void doWork();
	virtual std::shared_ptr<TimeOut> getNextTimeout()=0;
	double getInterval();
	void setInterval(double inter);
protected:
	double interval{2.0};
};

class SchedTimeOut : public TimeOut
{
public:
	SchedTimeOut(double time, bool renew=true) : TimeOut(time, renew){eventType=schedTimeOut;};
	std::shared_ptr<TimeOut> getNextTimeout();
	std::string getName();
};

class UsageUpdate : public TimeOut
{
public:
	UsageUpdate(double time, bool renew=true) : TimeOut(time, renew){eventType=usageUpdate;};
	std::string getName() override;
	void doWork() override;
	std::shared_ptr<TimeOut> getNextTimeout() override;
protected:
};

class StatsTick : public TimeOut
{
public:
	StatsTick(double time, bool renew = true) : TimeOut(time,renew){eventType=statsTick;};
	std::string getName() override;
	void doWork() override;
	std::shared_ptr<TimeOut> getNextTimeout() override;
};

class FreqUpdate : public TimeOut
{
public:
	FreqUpdate(double time, bool renew=true) : TimeOut(time, renew){eventType=freqUpdate;};
	std::string getName();
	std::shared_ptr<TimeOut> getNextTimeout() override;
	void doWork() override;
};
class DummyEvent : public TimeOut
{
public:
	DummyEvent(double time, bool renew = true) : TimeOut(time, renew){eventType=nothing;};
	std::string getName() override;
	std::shared_ptr<TimeOut> getNextTimeout() override;
	void doWork() override;
};

}
#endif
