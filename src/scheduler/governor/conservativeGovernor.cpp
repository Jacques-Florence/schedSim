/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "conservativeGovernor.h"

#include <algorithm>

#include <utils/log.h>

#include <scheduler/time.h>
#include <scheduler/processor.h>
#include <scheduler/system.h>

using namespace Scheduler;

ConservativeGovernor::ConservativeGovernor() : 
	maxFreq(System::getInstance()->getProc()->getMaxFreq()), minFreq(System::getInstance()->getProc()->getMinFreq())
{
}

void ConservativeGovernor::updateFreq(Processor *proc, Queue * /*readyQueue*/)
{
	/*TODO not finished*/
	double currentFreq = proc->getFreq();
	if (proc->getUsage() > upThreshold)
	{
		currentFreq = std::min(maxFreq, currentFreq + freqStep*maxFreq);
	}
	else if (proc->getUsage() < downThreshold)
	{
		currentFreq = std::max(minFreq, currentFreq - freqStep*maxFreq);
	}
	proc->setFreq(currentFreq);
}

bool ConservativeGovernor::freqChangeEvent(TriggeringEvent trigger)
{
	return (trigger == freqUpdate);
}

std::string ConservativeGovernor::getName()
{
	return "ConservativeGovernor";
}
