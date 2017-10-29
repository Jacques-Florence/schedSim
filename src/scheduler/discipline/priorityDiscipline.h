/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef PRIORITYDISCIPLINE_H
#define PRIORITYDISCIPLINE_H

#include "schedulingDiscipline.h"
#include <memory>

namespace Scheduler
{

class PriorityDiscipline : public SchedulingDiscipline
{
public:
	PriorityDiscipline(std::shared_ptr<SchedulerConfiguration> c) : SchedulingDiscipline(c){};//TODO: do we need a constructor if it's pure virtual?
	virtual ~PriorityDiscipline(){};
	
	typedef bool (*ComparatorPointer)(std::shared_ptr<Process> , std::shared_ptr<Process> );

	std::shared_ptr<Process> selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int);
	virtual bool preempts(TriggeringEvent trigger);
	virtual std::string getName()=0;
protected:
	/**@brief sets the correct priorities to the tasks, especially if dynamic priorities are used.
	 */
	virtual void updatePriorities(Queue *readyQueue, std::shared_ptr<Process> running);
	/**@brief return a function pointer to a function that provides comparison of tasks' priorities
	 * @return a pointer to a function taking two processes as arguments, and returning a boolean value.
	 * The return value is true if the first argument task's priority is higher than the second one.
	 */
	virtual  ComparatorPointer getComparator();
};

}

#endif
