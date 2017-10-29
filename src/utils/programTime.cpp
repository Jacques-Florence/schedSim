/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "programTime.h"
#include <chrono>

using namespace Utils;

clock_t ProgramTime::tp;

void ProgramTime::init()
{
	tp = clock();
}

double ProgramTime::elapsedTimeInSeconds()
{
	auto tp2 = clock();
	auto timeSpan = (double)(tp2-tp)/CLOCKS_PER_SEC;
	return timeSpan;
}


