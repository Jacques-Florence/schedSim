/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "eventList.h"

#include <cassert>
#include <iostream>

#include "event.h"

using namespace Scheduler;

EventList *EventList::instance = nullptr;
std::mutex EventList::mut;

EventList *EventList::getInstance()
{
	std::lock_guard<std::mutex> guard(mut);
	if (instance == nullptr)
	{
		instance = new EventList();
	}
	return instance;
}


EventList::EventList()
{
}

void EventList::setRandomGenerator(Utils::RandomGenerator *gen)
{
	randomGenerator = gen;
}

Utils::RandomGenerator *EventList::getRandomGenerator()
{
	return randomGenerator;
}

std::shared_ptr<Event> EventList::pop()
{
	std::lock_guard<std::mutex> guard(mut);
	std::shared_ptr<Event> e = list.front();
	list.pop_front();
	return e;
}


std::shared_ptr<Event> EventList::insert(std::shared_ptr<Event> e)
{
	std::lock_guard<std::mutex> guard(mut);
	if (e == nullptr)
		return nullptr;
	double time = e->getTime();

	if(time > endTime)
		return nullptr;

	
	auto p = list.end();
	while(p != list.begin())
	{
		if ((*--p)->getTime() <= time)
		{
			p++;
			break;
		}
	}
	auto it = list.insert(p, e);
	assert(e == (*it));
	return e;
}



void EventList::remove(std::shared_ptr<Event> e)
{
	std::lock_guard<std::mutex> guard(mut);
	for (auto it = list.begin(); it != list.end(); it++)
	{
		if (e.get() == (*it).get())
		{
			assert(e != nullptr);
			list.erase(it);
			return;
		}
	}
}


bool EventList::isEmpty()
{
	std::lock_guard<std::mutex> guard(mut);
	return (emptied ? true : (list.begin() == list.end()));
}

void EventList::empty()
{
	std::lock_guard<std::mutex> guard(mut);
	emptied = true;
}


void EventList::print()
{
	std::lock_guard<std::mutex> guard(mut);
	std::cout << "Printing the event list:\n";
	for (auto it = list.begin(); it != list.end(); it++)
	{
		assert((*it) != nullptr);
		std::cout << "    ";
		(*it)->print();
	}
}


std::shared_ptr<Event> EventList::getHead()
{
	std::lock_guard<std::mutex> guard(mut);
	return (*list.begin());
}


















