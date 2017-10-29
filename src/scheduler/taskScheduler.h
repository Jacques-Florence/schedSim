/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#include <memory>

#include <utils/record.h>

#include "events/eventList.h"
#include "events/eventType.h"

namespace Scheduler
{

class Event;
class FreqGovernor;
class Process;
class Queue;
class SchedulerConfiguration;
class SchedulingDiscipline;
class TemperatureModel;

class TaskScheduler
{
public:
	TaskScheduler(std::shared_ptr<SchedulerConfiguration> conf);
	~TaskScheduler();
	/**@brief This function is the scheduler.
	 * When called, it schedule the task to be executed on the processor amaong the tasks in the ready queue.
	 * The actual algorithm that selects the best task is found in the SchedulingDiscipline class.
	 * @param trigger the kind of event that triggered the scheduler invocation.
	 * This is needed to let the discipline know if it should act on the event, or skip it.
	 * This is bad design. I should rather make use of polymorphism.
	 * However I haven't found a better way to implement it so that
	 * a) the events stay independent from the discipline, and
	 * b) the disciplines stay easy to code, and don't have to be updated if a new event is added.
	 * The Visitor pattern, the Acyclic Visitor pattern and the Observer pattern all failed to provide a solution.
	 */
	void scheduleTask(TriggeringEvent trigger);
	/**@brief 
	 * 
	 */
	void clearRunningTask(std::shared_ptr<Process> p);
	/**@brief to be called when a deadline mis event happends.
	 * This function will terminate the task and update the performance counter.
	 * @param p the task that missed its deadline 
	 */
	void dealWithMissedDeadlines(std::shared_ptr<Process> p);
	/**@brief cleanup and print reports
	 */
	void end(std::string reportsFolder);


//those should be private but public for test purposes atm	
	void scheduleEndOfBurst(std::shared_ptr<Process> runningTask);
	void putRunningTaskBackToReadyQueue(std::shared_ptr<Process> task);
	void setDiscipline(std::unique_ptr<SchedulingDiscipline> discipline);
	void printDeadlineMissesReport(std::string folder);
	void printReports(std::string folder);
	void printStatus();
	void printRunningProcess(std::shared_ptr<Process> runningTask);
	void printInvocation();
	
	std::unique_ptr<SchedulingDiscipline> discipline;
	
	std::shared_ptr<Process> runningTask{nullptr};
	std::shared_ptr<Event> burstEnd;
	void setBurstEnd(std::shared_ptr<Event> e);
	std::shared_ptr<Event> getBurstEnd();
	unsigned int deadlineMisses{0};
	Utils::Record deadlinesHistory;
	
	double previousTime{0.0};
	std::shared_ptr<SchedulerConfiguration> conf;
	
};

}

#endif
