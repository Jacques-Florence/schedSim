/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef QUEUE_H
#define QUEUE_H

#include <iterator>
#include <list>
#include <string>
#include <memory>

namespace Scheduler
{

class Process;

/*TODO put the queues in the system class*/

/**@brief This class implements the ready queue and the wait queue.
 * Those queues contain processes ready to run and waiting for i/o respectively.
 */
class Queue
{
public:
	/**@brief get a pointer to the system's ready queue
	 */
	static Queue *getReadyQueue();
	/**@brief get a pointer to the system's wait queue
	 */
	static Queue *getWaitQueue();
private:
	/*Cannot use a shared_ptr because the constructor is private (singleton)*/
	static Queue *readyQueue;
	static Queue *waitQueue;
public:
	/**@brief add a process to the queue
	 */
	void add(std::shared_ptr<Process> p);
	/**@brief removes the process from the queue.
	 * Note: this does not delete the process. Just remove it from queue.
	 * @param p a pointer to the process to remove
	 * @return a pointer to the process if it was indeed in the queue, or nullptr otherwise
	 */
	std::shared_ptr<Process> remove(std::shared_ptr<Process> p);

	typedef std::list<std::shared_ptr<Process> >::iterator iterator;
	iterator begin();
	iterator end();
	size_t size() const;
	bool isEmpty() const;
	/**@brief print a summary of the queue's content
	 */
	void print() const;
	/**@brief get the queue's content as a string, for command-line output
	 */
	std::string getDisplay() const;
	/**@brief get the maximum size of the queues
	 */
	int getMaxSize() const;
private:
	Queue(); //singleton
	std::list<std::shared_ptr<Process> > queue;
	std::string queueDisplay;
};

}


#endif
