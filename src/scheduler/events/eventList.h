/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <cmath>
#include <list>
#include <memory>
#include <mutex>

#include "event.h"

namespace Utils{class RandomGenerator;}

namespace Scheduler
{

class Event;

/**The event list contains all the events scheduled and not yet processed
*/
class EventList
{

public:
	typedef std::list<std::shared_ptr<Event>>::iterator iterator;
	/**@brief Singleton pattern
	 *@return the one and only event list
	 */
	static EventList *getInstance();
	/**Removes and returns the event at the head of the list
	 * @return the event at the head of the list
	 * (the element the closest in the future)
	 */
	std::shared_ptr<Event> pop();
	/**@brief get the element at the head of the list
	 */
	std::shared_ptr<Event> getHead();
	/**Insert an event. The position will depend on the event's time
	 * If the event's time is after the simulation's end time,
	 * the event is not inserted.
	 * @param e a pointer to the event to be inserted. If the pointer is null,
	 * nothing is inserted.
	 * @return the event inserted, or nullptr if the element is not inserted
	 */
	std::shared_ptr<Event> insert(std::shared_ptr<Event> e);
	/**@brief remove an element from the list.
	 * @param e pointer to an event to be removed.
	 * If the list does not contain this event, nothing happens.
	 */
	void remove(std::shared_ptr<Event> e);
	/**Removes all elements from the list
	 */
	void empty();
	/**Tests if the list is empty
	 * @return true if the list is empty, false otherwise
	 */
	bool isEmpty();
	/**Print the contents of the list to standard output
	 */
	void print();
	/**@brief set a random generator
	 TODO: shouldn't that be part of the constructor?
	 */
	void setRandomGenerator(Utils::RandomGenerator *gen);
	/**@brief get the random generator
	 * @return a random generator
	 * 
	 * NOTE: this generator can be used by the events when needed.
	 * We make it go through the event list as a way to let the SchedulingSimulator class initialize the seed.
	 * FIXME: the SchedulingSimulator also provides a rng to the Process class, but through a static member
	 */
	Utils::RandomGenerator *getRandomGenerator();
private:
	EventList();
	static EventList *instance;
	std::list<std::shared_ptr<Event>> list;
	double endTime{INFINITY};
	bool emptied{false};
	Utils::RandomGenerator *randomGenerator;
	static std::mutex mut;
};



}


#endif
