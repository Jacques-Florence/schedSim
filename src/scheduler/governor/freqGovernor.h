/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef FREQGOVERNOR_H
#define FREQGOVERNOR_H

#include <string>

#include <scheduler/events/eventType.h>
#include <scheduler/processor.h>

namespace Scheduler
{

class Queue;
class Processor;

class FreqGovernor
{
public:
	virtual ~FreqGovernor(){};
	virtual void updateFreq(Processor *proc, Queue *readyQueue)=0;
	virtual bool freqChangeEvent(TriggeringEvent trigger)=0;
	virtual std::string getName()=0;
	virtual void printReport(std::string /*folder*/){};
};

}

#endif
