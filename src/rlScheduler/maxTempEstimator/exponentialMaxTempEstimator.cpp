/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "exponentialMaxTempEstimator.h"

#include <cmath>

#include <scheduler/system.h>
#include <scheduler/processor.h>

using namespace RlScheduler;

ExponentialMaxTempEstimator::ExponentialMaxTempEstimator(double sc, double off) :
	proc(Scheduler::System::getInstance()->getProc()), scaling(sc), offset(off)
{
}

double ExponentialMaxTempEstimator::getMaximumTemperature()
{
	return exp((proc->getTemperature() + offset)*scaling);
}

