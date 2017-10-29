/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "countingWheel.h"


using namespace Utils;


CountingWheel::CountingWheel(unsigned int b) : base(b)
{
}

void CountingWheel::initialize()
{
	value = 0;
}

bool CountingWheel::increment()
{
	if (base == 0)
		return true;
	value++;
	if (value == base)
	{
		value = 0;
		return true;
	}
	return false;
}

unsigned int CountingWheel::getValue()
{
	return value;
}



unsigned int CountingWheel::getBase()
{
	return base;
}
