/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef FIXEDPRIORITYDISCIPLINE_H
#define FIXEDPRIORITYDISCIPLINE_H

#include "priorityDiscipline.h"

namespace Scheduler
{

class FixedPriorityDiscipline : public PriorityDiscipline
{
public:
	static constexpr const char *configKey = "fixedPriorityDiscipline";
public:
	FixedPriorityDiscipline(std::shared_ptr<SchedulerConfiguration> c) : PriorityDiscipline(c){};
	~FixedPriorityDiscipline(){};
	std::string getName();
	void updatePriorities(Queue *readyQueue, std::shared_ptr<Process> running) override;
};

}

#endif
