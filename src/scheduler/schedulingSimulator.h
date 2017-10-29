/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <ctime>
#include <memory>

#include <utils/randomGenerator.h>

namespace Scheduler
{

/**@brief The main class of the simulator.

*/
class SchedulerConfiguration;
class Process;
class TaskSetGenerator;

class SchedulingSimulator
{
friend TaskSetGenerator;
public:
	SchedulingSimulator();
	/**@brief This constructor must be used when using
	 * a custom configuration file name or extensions
	 */
	SchedulingSimulator(std::shared_ptr<SchedulerConfiguration> conf);
	~SchedulingSimulator();
	/**@brief Builds the task set using a variety of methods
	 * This function is an alternative to using createRealTimeTask(),
	 * createInteractiveProcess(), or TaskSetGenerator::generate()
	 * and should be called before starting the simulation.
	 */
	void initializeTaskSet();
	/**@brief creates a new real-time task event
	 * and add it to the event scheduling queue
	 * @param startTime the time at which the first job spawns
	 * @param period the interval at which jobs are spawned
	 * @param wcet the amount of work a job has to do before the deadline.
	 * This is not a time, because the time to process it depends on
	 * the processor frequency.
	 * @param deadline the interval from the time where a job is spawned
	 * to the time it has to be completed. If this value is 0.0,
	 * the deadline is the period.
	 * @param priority
	 * @param isRandom determines if the amount of work is random.
	   In that case wcet is the worst-case amount of work
	 * @param bcet best case amount of work
	 */
	std::shared_ptr<Process> createRealTimeTask(
		double startTime,
		double period,
		double wcet,
		double deadline = 0.0,
		int priority = 0,
		double bcet = 0.0,
		double powerCoeff = 1.0
		);
	/**@brief creates a new interactive process event
	 *  and adds it to the event scheduling queue
	 * @param startTime the time at which the process is created
	 */
	void createInteractiveProcess(double startTime);
	/**@brief set the end of the simulation
	 * @param time the time at which to end simulation
	 */
	void endSimulation(double time);
	/**@brief seeds the random generator
	 * @param seed The seed has a time_t type,
	 * so it can be seeded with the current time
	 * in order to have better randomness.
	 * But a constant number can also be used for repeatability
	 */
	void seedRandomGenerator(time_t seed);
	/**@brief
	 * @param start the time at which the first timeout occurs
	 * @param interval the interval at which the next timeouts appear
	 * @sa StatsTick
	 */
	void setStatsTick(double start, double interval);
	/**@brief Sets a UsageUpdate timeout 
	 * @param start the time at which the first timeout occurs
	 * @param interval the interval at which the next timeouts will occur
	 * @sa UsageUpdate
	 */
	void setUsageCalculationTimeout(double start, double interval);
	/**@brief Sets a timer at the end of which the frequency governor
	 * updates the frequency of processor
	 * @param start the time at which the first timer gets off
	 * @param interval the interval of time between two timeouts
	 */
	void setFreqUpdate(double start, double interval);
	/**@brief sets the timeout at which the task scheduler is invoked
	 * @param start the time at which the scheduler is invoked for the first time
	 * @param interval the interval at which the timer is invoked
	 */
	void setSchedulerTimeout(double start, double interval);
	/**
	 */
	void setDummyEvent(double start, double interval);
	/**@brief turns on the processor
	 * @param start the time at which to start the processor
	 */
	void turnOnProcessor(double start);
	/**@brief call this function to launch the simulation
	 */
	void startScheduler();
private:
	void initializeTaskSetFromXml();
	void initializeTaskSetRandomly();
	void initializeTaskSetAtCompileTime();
	double previousTime{0.0};
	Utils::RandomGenerator randomGenerator;
	std::shared_ptr<SchedulerConfiguration> conf;
};

}

#endif
