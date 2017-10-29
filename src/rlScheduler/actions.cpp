/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "actions.h"

#include <cassert>

#include <scheduler/process.h>
#include <scheduler/queue.h>

#include "domainModel.h"

using namespace RlScheduler;


Action::Action(int pid) : id(pid)
{
}


void Action::performAction()
{
}


std::shared_ptr<Scheduler::Process> Action::getProcessToRun()
{
	//std::cout << "RL algo selected process "<<id<<"\n";
	std::shared_ptr<DomainModel> model = getModel<DomainModel>();
	std::shared_ptr<Scheduler::Process> process;
	if (model->running != nullptr && model->running->getPid() == id)
		return model->running;
	for (auto it = model->readyQueue->begin(); it != model->readyQueue->end(); it++)
	{
		assert((*it) != nullptr);
		if ( (*it)->getPid() == id)
			return (*it);
	}
	return process;
}

std::string Action::getName()
{
	return ("scheduling process " + id);
}









SleepAction::SleepAction()
{
}


void SleepAction::performAction()
{
}

std::string SleepAction::getName()
{
	return "sleep";
}


std::shared_ptr<Scheduler::Process> SleepAction::getProcessToRun()
{
	return nullptr;
}






