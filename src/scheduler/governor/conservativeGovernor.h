/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef CONSERVATIVEGOVERNOR_H
#define CONSERVATIVEGOVERNOR_H

#include "freqGovernor.h"

namespace Scheduler
{


class Queue;

class ConservativeGovernor : public FreqGovernor
{
public:
	static constexpr const char *configKey = "conservativeGovernor";
public:
	ConservativeGovernor();
	~ConservativeGovernor(){};
	void updateFreq(Processor *proc, Queue *readyQueue);
	bool freqChangeEvent(TriggeringEvent trigger);
	std::string getName();
private:
	const double maxFreq;
	const double minFreq;

	const double samplingRate{10}; /*FIXME This is pretty much useless here for the moment*/
	const double upThreshold{0.95};
	const double downThreshold{0.75}; /*what value?*/
	const double samplingDownFactor{1.0};
	const double powersaveBias{0.0};
	const double freqStep {0.05};
};

}
#endif
