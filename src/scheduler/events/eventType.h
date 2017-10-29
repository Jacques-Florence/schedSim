/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef EVENTTYPE_H
#define EVENTTYPE_H

namespace Scheduler
{

enum TriggeringEvent {terminate, wait, ready, newprocess, schedTimeOut, freqUpdate, statsTick, usageUpdate,
	stop, startProc, missedDeadline, nothing};

}

#endif
