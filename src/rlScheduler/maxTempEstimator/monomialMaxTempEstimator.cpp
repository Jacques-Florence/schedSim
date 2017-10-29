/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "monomialMaxTempEstimator.h"

#include <scheduler/system.h>
#include <scheduler/processor.h>

using namespace RlScheduler;

MonomialMaxTempEstimator::MonomialMaxTempEstimator(int deg) :
	proc(Scheduler::System::getInstance()->getProc()), degree(deg)
{
}

double MonomialMaxTempEstimator::getMaximumTemperature()
{
	if (degree < 0)
		return 0.0;
	const double temp = proc->getTemperature();
	double result = 1.0;
	for (int i = 0; i < degree; i++)
	{
		result *= temp;
	}
	return result;
}

