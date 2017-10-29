/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SCHEDULINGDISCIPLINE_H
#define SCHEDULINGDISCIPLINE_H

#include <string>
#include <memory>

#include <scheduler/schedulerConfiguration.h>
#include <scheduler/events/eventType.h>

namespace Scheduler
{

class Process;
class Queue;

class SchedulingDiscipline
{
public:
	virtual ~SchedulingDiscipline(){};
	SchedulingDiscipline(std::shared_ptr<SchedulerConfiguration> c) : conf(c){};
	/**@brief select the best task to run at this point.
	 * @param readyQueue the ready queue
	 * @param running the currently running task
	 * @param deadlineMisses
	 * @return the next task to be run
	 */
	virtual std::shared_ptr<Process> selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int deadlineMisses)=0;
	/**@brief returns true if the argument is a scheduling trigger for this specific discipline
	 * @param trigger the type of the event that triggered the scheduling invokation
	 */
	virtual bool preempts(TriggeringEvent trigger)=0;
	/**@brief returns the name of that discipline
	 */
	virtual std::string getName()=0;
	
	virtual void end(){};
protected:
	std::shared_ptr<SchedulerConfiguration> conf{nullptr};
};

}

#endif
