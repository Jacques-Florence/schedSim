/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "specialMailbox.h"

#include <iostream>

#include "process.h"

using namespace Scheduler;

SpecialMailbox *SpecialMailbox::instance = nullptr;

SpecialMailbox *SpecialMailbox::getInstance()
{
	if (instance == nullptr)
		instance = new SpecialMailbox();
	return instance;
}




void SpecialMailbox::put(double currentTime, std::shared_ptr<Process> p)
{
	if (p == nullptr)
	{
		valid = false;
		return;
	}
	double period = p->getPeriod();
	double deadline = p->getDeadlineTime();
	double earliness = deadline - currentTime;
	
	if (earliness < period*fraction)
	{
		reward = maxCost*(earliness/(period*fraction)-1.0);
	}
	else
	{
		reward = 0.0;
	}
	valid = true;
}


double SpecialMailbox::get()
{
	return reward;
}


void SpecialMailbox::invalidate()
{
	valid = false;
}



bool SpecialMailbox::isValid()
{
	return valid;
}



