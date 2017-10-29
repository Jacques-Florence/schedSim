/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlDiscipline.h"

#include <iostream>
#include <cassert>
#include <memory>

#include <utils/log.h>
#include <utils/math.h>

#include <scheduler/process.h>
#include <scheduler/queue.h>
#include <scheduler/system.h>
#include <scheduler/time.h>
#include <scheduler/specialMailbox.h>

#include <mdp/mdpModel.h>
#include <mdp/mdpConfiguration.h>

#include "rlDisciplineBuilder.h"
#include "actions.h"
#include "configuration.h"
#include "domainModel.h"

#define MISSED_DEADLINE_REWARD -1.0

using namespace RlScheduler;

RlDiscipline::RlDiscipline(std::shared_ptr<Configuration> c) : SchedulingDiscipline(c)
{
	construct();
}

RlDiscipline::~RlDiscipline()
{
	if (mdpModel != nullptr)
		delete mdpModel;
}


void RlDiscipline::construct()
{
	RlDisciplineBuilder::buildRlDisciplineModels(this);
	mdpModel->init();
}



std::shared_ptr<Scheduler::Process>
RlDiscipline::selectNextTask(Scheduler::Queue *readyQueue,
                             std::shared_ptr<Scheduler::Process> running,
                             unsigned int deadlineMisses)
{
	currentDeadlineMisses = deadlineMisses;
	model->running = Scheduler::System::getInstance()->getProc()->getRunningTask();
	bool processNotReady = true;
	std::shared_ptr<Scheduler::Process> process = nullptr;
	
	updateReward();
	Action *action = nullptr;


	int counter = 0; /*FIXME: not pretty*/
	do
	{
		counter++;
		action = static_cast<Action*>(mdpModel->selectAction()); //FIXME: should use dynamic_cast, but static_cast is faster
		if (readyQueue->isEmpty())
			return running;
		assert(action != nullptr);
		process = action->getProcessToRun();
		if (process == nullptr)
			model->reward = -HUGE_VAL;
		else
			processNotReady = false;
	} while (processNotReady && counter < 1000);
	if (counter >= 1000)
	{
		if (Scheduler::Queue::getReadyQueue()->isEmpty())
			return nullptr;
		return *(Scheduler::Queue::getReadyQueue()->begin());
	}
	action->performAction();
	return process;
}

bool RlDiscipline::preempts(Scheduler::TriggeringEvent trigger)
{
	return ((trigger == Scheduler::TriggeringEvent::newprocess)
	        || (trigger == Scheduler::TriggeringEvent::ready));
	return true;
}


void RlDiscipline::updateReward()
{
	/*We look at the ready queue and the running process.
	If one of them has crossed its deadline in the last iteration,
	a bad cost is incurred.
	TODO: an improvement would be to measure the time at which a job completes,
	and incur a reward proportional to the time between completion and deadline
	(positive reward if before deadline, negative if after.)
	UPDATE: partially done...*/
	model->reward = (currentDeadlineMisses - previousDeadlineMisses);
	model->reward *= MISSED_DEADLINE_REWARD;
	previousDeadlineMisses = currentDeadlineMisses;
	Scheduler::SpecialMailbox *mailbox = Scheduler::SpecialMailbox::getInstance();
	static bool softDeadline = conf->getBoolValue("rlDiscipline", "softDeadline", false);
	
	if (softDeadline)
	{
		if (mailbox->isValid())
		{
			//std::cerr << "before: "<< model->reward<<"\n";
			model->reward += mailbox->get();
			//std::cerr << "after: "<< model->reward<<"\n";
			mailbox->invalidate();
		}
	}
}




void RlDiscipline::end()
{
	model->end();
	mdpModel->end();
}





