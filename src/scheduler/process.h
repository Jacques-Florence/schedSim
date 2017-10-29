/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef PROCESS_H
#define PROCESS_H

#include <cmath>
#include <iterator>
#include <list>
#include <ostream>
#include <vector>
#include <memory>

namespace Utils
{
	class RandomGenerator;
	class BoundedRandomDistribution;
}

namespace Scheduler
{

class Event;

class Process
{
public:
	/**@brief create the next job for a task
	 */
	static std::shared_ptr<Process> createNextJob(const Process& task);
	/**@brief creates an "interactive" process
	 * @param cpuLambda is the lambda parameter of the exponential distribution
	 * used to randomly generate the cpu bursts
	 * @param ioLambda is the lambda parameter of the exponential distribution
	 * used to randomly generate the io burst durations
	 */
	static std::shared_ptr<Process> createProcess(double cpuLambda, double ioLambda);
	/**@brief creates a real time task
	 * @param aow amount of work to be performed by each job
	 * @param T period between two consecutive jobs are issued
	 * @param dl deadline, relative to the time at which the job was issued
	 * @param pid process identifier
	 * @param priority is for scheduling algos with prioirty lists
	 * @param bcet best vase execution time
	 */
	static std::shared_ptr<Process> createRealTimeTask(double wcet, double T,
		double dl, int pid, int priority = 0, double bcet = 0.0);
	/**@brief returns new process identifier. The value returned gets incremented at each call
	 */
	static int getNewPid();
	/**@brief returns the maximum number of process that can ever be created
	 *
	 * This is needed by some MDP algorithms
	 */
	static unsigned long int getMaxNumber();
	/**@brief specify what random generator to use for interactive task length
	 */
	static void setRandomGenerator(Utils::RandomGenerator *gen);

	/**@brief call this function before any other
	 */
	//static void init();

	/**@brief call this function at the end of the simulation
	 */
	static void end();
private:
	static const unsigned long int maxNumber = 4000000000;
	static unsigned long  int currentNumber;
	static Utils::RandomGenerator *randomGenerator;
public:
	/*FIXME: Why are those public?*/
	Process(int pid, int nbBursts, std::vector<double> cpuBursts, std::vector<double> ioBursts, int priority = 0);
	Process(const Process& task);
	~Process();
	
	void setDurationDistribution(std::shared_ptr<Utils::BoundedRandomDistribution> randomDist);
	int getPid(void) const;
	int getPriority() const;
	void setPriority(int pri);
	void updateCurrentAow(double aow);
	bool advanceBurst();
	void decrementBurst();
	double getCurrentCpuAow() const;
	double getCurrentIoTime() const;
	void setRtParams(double dl, double T, double wcet, double bcet);
	void setDeadlineTimeFromStartTime(double startTime);//TODO: how does this work with AOW?
	bool isRealTime() const;
	double getPeriod() const;
	double getDeadline() const;
	double getDeadlineTime() const;
	void print(std::ostream& stream) const;
	void incrementJobNumber();//TODO: Why is this public?
	unsigned int getJobNumber() const;
	double getWcet() const;
	void setPowerCoeff(double);
	double powerCoeff{1.0}; /*FIXME make this private*/
private:
	/*Only for real-time jobs*/
	void setDuration();

	int pid;
	std::vector<double> cpuBurst;/*This is an array of aow. For RT jobs, this contains only one number*/
	std::vector<double> ioBurst;/*This is an array of times spent waiting*/
	int currentBurst{0};
	int nbBursts; /*This is the nb of cpu bursts. there are n-1 io bursts.*/
	int priority{0};

	/*Those are the real time parameters. Maybe would it be better to put them in an aggregated class*/
	bool RT{false};
	double deadline{0.0};
	double deadlineTime{0.0};
	double period{INFINITY};
	unsigned int jobNumber{0};
	double bcet{0.0}; /*best case execution time*/
	double wcet{0.0}; /*XXX: wcet and bcet are expressed as amount of work and not in time units.*/	
	std::shared_ptr<Utils::BoundedRandomDistribution> randomDist{nullptr};
};




}


#endif
