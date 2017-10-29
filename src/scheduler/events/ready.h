/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef READY_H
#define READY_H

#include <memory>

#include "event.h"

namespace Scheduler
{

/**This event is scheduled when a waiting process becomes ready
 */
class Ready : public Event
{
public:
	Ready(double time, bool renew=false) : Event(time, renew){eventType=ready;};
	void process() override;
	std::string getName() override;
};

}

#endif
