/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "fixedPriorityDiscipline.h"

using namespace Scheduler;

std::string FixedPriorityDiscipline::getName()
{
	return "Fixed priority";
}

void FixedPriorityDiscipline::updatePriorities(Queue *, std::shared_ptr<Process>)
{
	/*note that this redefinition is not necessary, as the default PriorityDiscipline already
	implements a fixed priority. This redefinition is an optimization.*/
	return;
}


