/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "schedulerActions.h"

#include <memory>
#include <stdexcept>

#include <scheduler/queue.h>
#include <scheduler/system.h>
#include <scheduler/processor.h>

#include "schedulerDomainModel.h"

using namespace MdpGov;

std::string SetMinFreq::getName()
{
	return "Set min freq";
}

void SetMinFreq::performAction()
{
	getModel<SchedulerDomainModel>()->proc->setFreq(getModel<SchedulerDomainModel>()->proc->getMinFreq());
}

std::string SetMaxFreq::getName()
{
	return "SetMaxFreq";
}

void SetMaxFreq::performAction()
{
	getModel<SchedulerDomainModel>()->proc->setFreq(getModel<SchedulerDomainModel>()->proc->getMaxFreq());

}
