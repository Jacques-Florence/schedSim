/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NEW_PROCESS_H
#define NEW_PROCESS_H

#include <memory>
#include "event.h"

namespace Scheduler
{


/**A new process appears
 */
class NewProcess : public Event
{
public:
	NewProcess(double time, bool renew=true) : Event(time, renew){eventType=newprocess;};
	virtual ~NewProcess();
	virtual void process()=0;
	virtual std::string getName()=0;
protected:
	void queueProcess(std::shared_ptr<Process> p);
	virtual void scheduleNextEvent()=0;
	virtual std::shared_ptr<Process> createTask()=0;
};

}

#endif
