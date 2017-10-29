/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MISSED_DEADLINE_H
#define MISSED_DEADLINE_H

#include <memory>

#include "event.h"

namespace Scheduler
{

/**This event checks whether a process misses its deadline and deals with it.
 */
class MissedDeadline : public Event
{
public:
	MissedDeadline(double time) : Event(time, false){eventType=missedDeadline;};
	void process();
	std::string getName();
	void print() override;
private:

};

}


#endif
