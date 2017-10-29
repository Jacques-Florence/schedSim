/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SPECIAL_MAILBOX_H
#define SPECIAL_MAILBOX_H

#include <memory>

namespace Scheduler
{
class Process;
class SpecialMailbox
{
public:
	static SpecialMailbox *getInstance();
private:
	static SpecialMailbox *instance;
public:
	void put(double currentTime, std::shared_ptr<Process> p);
	double get();
	void invalidate();
	bool isValid();
private:
	SpecialMailbox(){};
	double reward{0.0};
	bool valid{false};
	const double maxCost{1.0}; //what value for this ?
	//right now it is the value of MISSED_DEADLINE_REWARD in rlDiscipline.cpp
	const double fraction{0.05};
};
}

#endif
