/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "envelopeDetector.h"

#include <scheduler/system.h>
#include <scheduler/processor.h>

using namespace RlScheduler;

EnvelopeDetector::EnvelopeDetector(double d) : 
	decayCoeff(d),
	proc(Scheduler::System::getInstance()->getProc())
{
}

double EnvelopeDetector::getMaximumTemperature()
{
	/*FIXME using exponential decay this way makes the max temperature converge
	to 0 degrees Celcius. There is no reason for that. To what value should we make it converge?
	To average temperature? absolute zero? ambient temperature? ...
	I would say average temperature. But a bit complicated to implement...*/
	maxTemp *= decayCoeff;
	double currentTemp = proc->getTemperature();
	maxTemp = (maxTemp > currentTemp) ? maxTemp : currentTemp;
	return maxTemp;
}
