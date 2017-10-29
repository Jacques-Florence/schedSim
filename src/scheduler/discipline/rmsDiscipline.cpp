/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rmsDiscipline.h"

#include <algorithm>

#include <scheduler/process.h>

using namespace Scheduler;

std::string RmsDiscipline::getName()
{
	return "Rate Monotonic Scheduling Discipline";
}


PriorityDiscipline::ComparatorPointer RmsDiscipline::getComparator()
{
	return [](std::shared_ptr<Process> a, std::shared_ptr<Process> b){return a->getPeriod() < b->getPeriod();};
}














