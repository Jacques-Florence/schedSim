/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>

#include "governor/freqGovernor.h"

namespace Scheduler
{

class Processor;
class SchedulerConfiguration;
class Process;
class TaskScheduler;

class System
{
public:
	static void buildSystem(std::shared_ptr<SchedulerConfiguration> conf);
	static System *getInstance();
private:
	static System *instance;
public:
	~System();
	/**@brief returns the task scheduler object
	 */
	TaskScheduler *getScheduler();
	/**@brief updates and logs the temperature of the processor.
	 * This function has to be called at least every time the task
	 * executed by the processor changes.
	 */
	void updateTemperature(double timeInterval);
	/**@brief invokes the frequency governor to changes the frequency of the processor
	 */
	void updateFreq();
	/**@brief return the processor
	 */
	Processor *getProc();
	/**@brief prints reports
	 */
	void end();
	/**@brief add a real-time task to the system's list
	 * @param p the task to be added
	 */
	void addRealTimeTask(std::shared_ptr<Process> p);
	/**@brief get the list of real-time tasks in the system
	 */
	std::vector<std::shared_ptr<Process>> getStaticTaskSet();
	/**@brief returns the number of jobs issued since the beginning of the simulation
	 */
	long long int getJobsArrivalCount();
	/**@brief increments the number of jobs issued since the beginning of simulation
	 */
	void incrementJobsArrivalCount();
	void printProcessesReport();
private:
	void printReports();
	System();	
	std::string reportsFolder;
	std::shared_ptr<SchedulerConfiguration> conf;
	Processor *proc{nullptr};
	TaskScheduler *scheduler{nullptr};
	FreqGovernor *governor{nullptr};
	/**This is used for real-time task sets
	 */
	std::vector<std::shared_ptr<Process>> staticTaskSet;

	long long int jobsArrivalCount;
};

}




#endif






