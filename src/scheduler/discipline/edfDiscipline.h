/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef EDFDISCIPLINE_H
#define EDFDISCIPLINE_H

#include <string>

#include "priorityDiscipline.h"

namespace Scheduler
{

class EdfDiscipline : public PriorityDiscipline
{
public:
	EdfDiscipline(std::shared_ptr<SchedulerConfiguration> c) : PriorityDiscipline(c){};
	~EdfDiscipline(){};
	static constexpr const char *configKey = "edfDiscipline";
protected:
	virtual std::string getName();
	PriorityDiscipline::ComparatorPointer getComparator() override;
};

}
#endif
