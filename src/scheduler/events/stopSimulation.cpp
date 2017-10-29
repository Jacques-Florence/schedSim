/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "stopSimulation.h"

#include <scheduler/system.h>
#include "eventList.h"

using namespace Scheduler;


void StopSimulation::process()
{
	std::cerr << "processing stopSimulation...\n";
	System::getInstance()->end();
	std::cerr << "system instance ended\n";
	EventList::getInstance()->empty();
	std::cerr << "event list emptied\n";
	print();
	std::cerr << "event name printed\n";
	return;
}

std::string StopSimulation::getName()
{
	return "Simulation stopped";
}



