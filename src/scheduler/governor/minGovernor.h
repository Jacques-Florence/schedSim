/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MINGOVERNOR_H
#define MINGOVERNOR_H


#include "freqGovernor.h"

namespace Scheduler
{

class MinGovernor : public FreqGovernor
{
public:
	static constexpr const char *configKey = "minGovernor";
public:
	MinGovernor();
	~MinGovernor(){};
	void updateFreq(Processor *proc, Queue *readyQueue);
	bool freqChangeEvent(TriggeringEvent trigger);
	std::string getName();
private:
	const double minFreq{1.0}; /*TODO: make this a constant and solve the resulting initialization problem*/
};

}

#endif
