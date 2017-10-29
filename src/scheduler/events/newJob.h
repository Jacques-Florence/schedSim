/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NEW_JOB_H
#define NEW_JOB_H

#include <memory>
#include <atomic>

#include "event.h"
#include "newProcess.h"

namespace Scheduler
{

/**A new job for a task is released
 */
class NewJob : public NewProcess
{
public:
	static void init();
private:
	static void initEventSchedulingThread();
	static void eventSchedulingThreadFunction();
	static std::atomic<bool> startEventScheduling;
	static NewJob* processBeingCreated;
public:
	NewJob(double time, bool renew=true) : NewProcess(time, renew){};
	void process() override;
	std::string getName() override;
private:
	std::shared_ptr<Process> createTask() override;
	void scheduleNextEvent() override;
	void scheduleMissedDeadlineEvent();
	int pid{-1};
};
}


#endif
