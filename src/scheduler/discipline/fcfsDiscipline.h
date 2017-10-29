/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef FCFSDISCIPLINE_H
#define FCFSDISCIPLINE_H

#include "schedulingDiscipline.h"

namespace Scheduler
{

class FcfsDiscipline : public SchedulingDiscipline
{
public:
	static constexpr const char *configKey = "fcfsDiscipline";
public:
	FcfsDiscipline(std::shared_ptr<SchedulerConfiguration> c) : SchedulingDiscipline(c){}
	~FcfsDiscipline(){};
	std::shared_ptr<Process> selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int deadlineMisses) override;
	std::string getName();
	bool preempts(TriggeringEvent trigger);
};

}

#endif
