/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RMSDISCIPLINE_H
#define RMSDISCIPLINE_H

#include <string>

#include "priorityDiscipline.h"

namespace Scheduler
{

class RmsDiscipline : public PriorityDiscipline
{
public:
	static constexpr const char *configKey = "rmsDiscipline";
public:
	RmsDiscipline(std::shared_ptr<SchedulerConfiguration> c) : PriorityDiscipline(c){};
	~RmsDiscipline(){};
protected:
	virtual std::string getName() override;
	PriorityDiscipline::ComparatorPointer getComparator() override;
};

}

#endif
