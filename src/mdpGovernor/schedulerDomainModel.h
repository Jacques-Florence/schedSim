/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SCHEDULERDOMAINMODEL_H
#define SCHEDULERDOMAINMODEL_H

#include <mdp/domainModel.h>

namespace Scheduler
{
	class Queue;
	class System;
	class Processor;
}

namespace MdpGov
{

class SchedulerDomainModel : public Mdp::DomainModel
{
public:
	double measureReward();

	Scheduler::Queue *readyQueue;
	Scheduler::Queue *waitQueue;
	Scheduler::Processor *proc;
};

}

#endif
