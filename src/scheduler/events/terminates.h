/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TERMINATES_H
#define TERMINATES_H

#include <memory>

#include "event.h"

namespace Scheduler
{


/**This event is scheduled when a process terminates
*/
class Terminates : public Event
{
public:
	Terminates(double time, bool renew=false) : Event(time, renew){eventType=terminate;};
	void process() override;
	std::string getName() override;
};

}

#endif
