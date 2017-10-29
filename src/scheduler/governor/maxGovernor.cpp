/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "maxGovernor.h"

#include <scheduler/queue.h>
#include <scheduler/processor.h>
#include <scheduler/system.h>

using namespace Scheduler;

MaxGovernor::MaxGovernor() : maxFreq(System::getInstance()->getProc()->getMaxFreq())
{
}

void MaxGovernor::updateFreq(Processor *proc, Queue * /*readyQueue*/)
{
	proc->setFreq(maxFreq);
}

bool MaxGovernor::freqChangeEvent(TriggeringEvent /*trigger*/)
{
	return true;
}

std::string MaxGovernor::getName()
{
	return "MaxGovernor";
}
