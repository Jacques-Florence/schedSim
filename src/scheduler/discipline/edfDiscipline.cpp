/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "edfDiscipline.h"

#include <algorithm>

#include <scheduler/process.h>

using namespace Scheduler;

std::string EdfDiscipline::getName()
{
	return "Earliest Deadline First Discipline";
}


PriorityDiscipline::ComparatorPointer EdfDiscipline::getComparator()
{
	return [](std::shared_ptr<Process> a, std::shared_ptr<Process> b){return a->getDeadlineTime() < b->getDeadlineTime();};
}
