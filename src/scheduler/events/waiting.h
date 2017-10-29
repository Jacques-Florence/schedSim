/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef WAITING_H
#define WAITING_H

#include <memory>

#include "event.h"

namespace Scheduler
{


/**This event is scheduled when a currently executing process needs to wait*/
class Waiting : public Event
{
public:
	Waiting(double time, bool renew=false) : Event(time, renew){eventType=wait;};
	void process() override;
	std::string getName() override;
};

}




#endif
