/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ROUNDROBINDISCIPLINE_H
#define ROUNDROBINDISCIPLINE_H

#include "schedulingDiscipline.h"
#include <memory>

namespace Scheduler
{

class Process;
class Queue;

class RoundRobinDiscipline : public SchedulingDiscipline
{
public:
	static constexpr const char *configKey = "roundRobinDiscipline";
public:
	RoundRobinDiscipline(std::shared_ptr<SchedulerConfiguration> c) : SchedulingDiscipline(c){};
	~RoundRobinDiscipline(){};
	std::shared_ptr<Process> selectNextTask(Queue *readyQueue, std::shared_ptr<Process> running, unsigned int);
	std::string getName();
	bool preempts(TriggeringEvent trigger);
private:
	std::shared_ptr<Process> currentProcess{nullptr};
};

}

#endif
