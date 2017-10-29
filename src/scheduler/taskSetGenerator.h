/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TASK_SET_GENERATOR_H
#define TASK_SET_GENERATOR_H


#include <utils/randomGenerator.h>

#include <memory>
#include <vector>

namespace Utils
{
	class RandomGenerator;
	class BoundedRandomDistribution;
}

namespace Scheduler
{

class SchedulingSimulator;
class SchedulerConfiguration;

class TaskSetGenerator
{
public:
	/**@brief generates a random task set.
	 * The deadline will be equal to the period.
	 * The start time will be 0.1
	 * The set is then saved in the System class,
	   in order to be accessed by some scheduling disciplines needing it.
	 * @param nbTasks the number of tasks
	 * @param utilization the total cpu utilization
	 * @param seed the seed to use for the random generator
	 * @param critical wether there is an hyperperiod
	 * at the start of which all tasks get issued
	 * Note: for the moment, critical is always true.
	 * @param integerPeriod if true, the period of each task is an integer.
	 * IMPORTANT: setting this to true modifies slightly the actual utilization
	 * compared to the specified value
	 * @param isRandom if true, the amount of work is random.
	 */
	static void generate(
		  SchedulingSimulator *simulator
		, unsigned int nbOfTasks
		, double utilization
		, time_t seed
		, bool critical = true
		, bool integerPeriod = false
		, std::shared_ptr<Utils::BoundedRandomDistribution> dist = nullptr
		);
private:
	static bool arePrioritiesEnabled(std::shared_ptr<SchedulerConfiguration> conf);
	/*The execution time (at constant freq) is defined as period * portion*/
	static std::vector<double> computeAow(
		  std::vector<double> periods
		, std::vector<double> portion
		, unsigned int nbOfTask
		);
	static std::vector<double> generateTaskPeriods(
		  unsigned int nbOfTasks
		, bool integerPeriod
		, Utils::RandomGenerator *gen
		);
	static std::vector<double> generateCpuUtilizationOfTasks(
		  unsigned int nbOfTasks
		, Utils::RandomGenerator *gen
		, double utilization
		);
	static void generateTasks(
		  std::vector<double> periods
		, std::vector<double> aow
		, Utils::RandomGenerator *gen
		, bool enablePriority
		, unsigned int nbOfTasks
		, bool critical
		, SchedulingSimulator *simulator
		, std::shared_ptr<Utils::BoundedRandomDistribution> dist
		);

	static constexpr const double maxT = 30.0; //maximum task period
	static constexpr const double minT = 5.0;  //minimum task period
};


}

#endif
