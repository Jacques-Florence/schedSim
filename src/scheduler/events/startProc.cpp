/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "startProc.h"

#include <scheduler/system.h>
#include <scheduler/processor.h>

using namespace Scheduler;


void StartProc::process()
{
	print();
	Processor *proc = System::getInstance()->getProc();
	proc->power(true);
	System::getInstance()->updateFreq();
}

std::string StartProc::getName()
{
	return "Starting processor";
}
