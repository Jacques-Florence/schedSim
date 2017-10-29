/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "mdpGovernor.h"

#include <cassert>
#include <string>
#include <memory>

#include <mdp/mdpModel.h>
#include <mdp/actionSpaceBuilder.h>
#include <mdp/stateSpaceBuilder.h>
#include <mdp/mdpConfiguration.h>

#include <scheduler/processor.h>
#include <scheduler/system.h>
#include <scheduler/queue.h>

#include "schedulerDimensions.h"
#include "schedulerActions.h"
#include "schedulerDomainModel.h"
#include "mdpGovernorConfiguration.h"

using namespace MdpGov;

MdpGovernor::MdpGovernor()
{
	std::shared_ptr<SchedulerDomainModel> domainModel = std::make_shared<SchedulerDomainModel>();
	domainModel->readyQueue = Scheduler::Queue::getReadyQueue();
	domainModel->waitQueue = Scheduler::Queue::getWaitQueue();
	domainModel->proc = Scheduler::System::getInstance()->getProc();

	Mdp::StateSpaceBuilder builder;
	builder.setDomainModel(domainModel);

	MdpGovernorConfiguration conf("configuration.conf");
	std::shared_ptr<Mdp::MdpConfiguration> mdpConf = std::make_shared<Mdp::MdpConfiguration>("configuration.conf"); /*FIXME this is ugly*/
	std::vector<Mdp::StateSpaceDimension*> dims = conf.getDimensionsFromFile();
	for (size_t i = 0; i < dims.size(); i++)
	{
		builder.addDimension(dims[i]);
	}

	std::shared_ptr<Mdp::StateSpace> stateSpace = builder.getStateSpace();

	Mdp::ActionSpaceBuilder abuilder;
	abuilder.setDomainModel(domainModel);
	abuilder.addAction(new SetMinFreq);
	abuilder.addAction(new SetMaxFreq);
	abuilder.setDomainModel(domainModel);
	std::shared_ptr<Mdp::ActionSpace> actionSpace = abuilder.getActionSpace();

	model = new Mdp::MdpModel(stateSpace, actionSpace, mdpConf);
}

MdpGovernor::~MdpGovernor()
{
	delete model;
}

void MdpGovernor::updateFreq(Scheduler::Processor * /*proc*/, Scheduler::Queue * /*readyQueue*/)
{
	static bool first = true;
	if (first)
	{
		first = false;
		model->init();
	}
	Mdp::Action *action = model->selectAction();
	action->performAction();
}


bool MdpGovernor::freqChangeEvent(Scheduler::TriggeringEvent trigger)
{
	if (trigger == Scheduler::TriggeringEvent::freqUpdate)
		return true;
	return false;
}



std::string MdpGovernor::getName()
{
	return "MDP Governor";
}


void MdpGovernor::printReport(std::string folder)
{
	model->printReportsToFile(folder);
}



































