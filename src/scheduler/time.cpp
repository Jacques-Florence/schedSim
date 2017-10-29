/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "time.h"

using namespace Scheduler;

double Time::time = 0.0;

double Time::getTime()
{
	return time;
}

void Time::updateTime(double t)
{
	time = t;
}

