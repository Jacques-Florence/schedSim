/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef START_PROC_H
#define START_PROC_H

#include <memory>

#include "event.h"

namespace Scheduler
{

/**
 * This event powers the processor and gives it an operating frequency
 */
class StartProc : public Event
{
public:
	StartProc(double time=0, bool renew=false) : Event(time, renew){eventType=startProc;};
	void process() override;
	std::string getName() override;
	
};

}

#endif
