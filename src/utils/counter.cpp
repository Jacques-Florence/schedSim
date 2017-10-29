/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "counter.h"
#include <cstdlib>

using namespace Utils;

Counter::~Counter()
{
	for (size_t i = 0; i < wheels.size(); i++)
	{
		delete wheels[i];
	}
}

void Counter::addWheel(unsigned int base)
{
	wheels.push_back(new CountingWheel(base));
}

void Counter::initialize()
{
	for (unsigned int i = 0; i < wheels.size(); i++)
	{
		wheels[i]->initialize();
	}
}

bool Counter::increment()
{
	bool overflow = false;
	for (unsigned int i = 0; i < wheels.size(); i++)
	{
		overflow = wheels[i]->increment();
		if (!overflow)
			break;
	}
	return overflow;
}

std::vector<unsigned int> Counter::getValue()
{
	std::vector<unsigned int> value(wheels.size());
	for (unsigned int i = 0; i < wheels.size(); i++)
	{
		value[i] = wheels[i]->getValue();
	}
	return value;
}



long long unsigned int Counter::getNumberOfValues()
{
	long long int value = 1;
	for (unsigned int i = 0; i < wheels.size(); i++)
	{
		value *= wheels[i]->getBase();
	}
	return value;
}

