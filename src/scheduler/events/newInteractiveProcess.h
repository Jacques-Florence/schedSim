/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NEW_INTERACTIVE_PROCESS_H
#define NEW_INTERACTIVE_PROCESS_H

#include <memory>

#include "event.h"
#include "newProcess.h"

namespace Scheduler
{

/**A new interactive process appears
 */
class NewInteractiveProcess : public NewProcess
{
public:
	NewInteractiveProcess(double time, bool renew=true) : NewProcess(time, renew){};
	void process() override;
	std::string getName() override;
private:
	double lambda;
	std::shared_ptr<Process> createTask() override;
	void scheduleNextEvent() override;
};

}


#endif
