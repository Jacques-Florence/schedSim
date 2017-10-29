/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "squareMaxTempEstimator.h"

#include <scheduler/system.h>
#include <scheduler/processor.h>

using namespace RlScheduler;

SquareMaxTempEstimator::SquareMaxTempEstimator() :
	proc(Scheduler::System::getInstance()->getProc())
{
}

double SquareMaxTempEstimator::getMaximumTemperature()
{
	const double temp = proc->getTemperature();
	return temp*temp;
}
