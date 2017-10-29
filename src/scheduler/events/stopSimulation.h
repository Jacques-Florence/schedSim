/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef STOP_SIMULATION_H
#define STOP_SIMULATION_H

#include <memory>

#include "event.h"

namespace Scheduler
{

/**This event is scheduled at the time  the simulation ends
*/
class StopSimulation : public Event
{
public:
	StopSimulation(double time, bool renew=false) : Event(time, renew){eventType=stop;};
	void process() override;
	std::string getName() override;
};

}

#endif
