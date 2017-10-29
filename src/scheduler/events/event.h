/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include <string>

#include "eventType.h"

#define PRINT 1
namespace Scheduler
{

class Process;
class EventList;
class Visitor;

class Event
{
friend EventList;
public:
	/** @brief Event constructor
	 *  @param time the time at which the event is to be scheduled
	 *  @param renew set this to true if the event has to be repeated (for periodic events).
	    It will then reschedule itself according to its behavior.
	 */
	Event(double time, bool renew = true);
	/**@brief if the event is specific to a task, set it here.
	 * TODO not all events have an associated task. This should be moved
	 */
	void setTask(std::shared_ptr<Process> task);
	/**@brief get the time at which the event is scheduled
	 * @return the time at which the event is scheduled
	 */
	double getTime();
	/**@brief handle the the event
	 * TODO: 'process' is maybe not the best word for that,
	 * given that our simulator actually manipulated processes
	 */
	virtual void process()=0;
	virtual ~Event();
	/**@brief print information about the event
	 */
	virtual void print();
	/**@brief get the name of the event
	 * @return a string containing the name of the event
	 */
	virtual std::string getName()=0;
protected:
	double time;
	bool renew;
	std::shared_ptr<Process> task{nullptr};
	/**@brief The event type is need by the scheduling discipline,
	 * to determine if this kind of event triggers invokatio of that discipline
	 */
	TriggeringEvent eventType{nothing};
};




}



#endif
