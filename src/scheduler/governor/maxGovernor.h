/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MAXGOVERNOR_H
#define MAXGOVERNOR_H

#include "freqGovernor.h"

namespace Scheduler
{

class MaxGovernor : public FreqGovernor
{
public:
	static constexpr const char *configKey = "maxGovernor";
public:
	MaxGovernor();
	~MaxGovernor(){};
	void updateFreq(Processor *proc, Queue *readyQueue);
	bool freqChangeEvent(TriggeringEvent trigger);
	std::string getName();
private:
	const double maxFreq{2.0}; /*TODO make this a const and solve the resulting initialization problem*/
};

}

#endif
