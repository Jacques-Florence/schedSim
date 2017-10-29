/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "minGovernor.h"

#include <scheduler/queue.h>
#include <scheduler/system.h>

using namespace Scheduler;

MinGovernor::MinGovernor() : minFreq(System::getInstance()->getProc()->getMinFreq())
{
}

void MinGovernor::updateFreq(Processor *proc, Queue * /*readyQueue*/)
{
	proc->setFreq(minFreq);
}

bool MinGovernor::freqChangeEvent(TriggeringEvent /*trigger*/)
{
	return true;
}

std::string MinGovernor::getName()
{
	return "MinGovernor";
}



