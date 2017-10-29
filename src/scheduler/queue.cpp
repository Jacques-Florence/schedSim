/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "queue.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "process.h"

using namespace Scheduler;

Queue *Queue::readyQueue = nullptr;
Queue *Queue::waitQueue = nullptr;

void Queue::add(std::shared_ptr<Process> p)
{
	queue.push_back(p);
	assert(p != nullptr);
}


Queue *Queue::getReadyQueue()
{
	if (!readyQueue)
		readyQueue = new Queue;
	return readyQueue;
}

Queue *Queue::getWaitQueue()
{
	if (!waitQueue)
		waitQueue = new Queue;
	return waitQueue;
}

Queue::Queue()
{
}

std::shared_ptr<Process> Queue::remove(std::shared_ptr<Process> p)
{
	if (p == nullptr)
		return nullptr;
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		if ((*it) == p)
		{
			queue.remove(p);
			return (p);
		}
	}
	return nullptr;
}



Queue::iterator Queue::begin()
{
	return queue.begin();
}
Queue::iterator Queue::end()
{
	return queue.end();
}


size_t Queue::size() const
{
	return queue.size();
}

bool Queue::isEmpty() const
{
	return (size() == 0);
}


void Queue::print() const
{
	std::cout << "The queue contains:\n";
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		std::cout << "    pid "<<(*it)->getPid()<<"\n";
	}
}

std::string Queue::getDisplay() const
{
	if (queue.empty())
	{
		return "nothing";
	}
	std::ostringstream stream;
	for (auto it = queue.begin(); it != queue.end(); it++)
	{
		stream << (*it)->getPid();
		if ((*it)->isRealTime())
			stream <<"("<<(*it)->getDeadlineTime()<<")";
		stream << " ";
	}
	return stream.str();
}





int Queue::getMaxSize() const
{
	return Process::getMaxNumber();
}








