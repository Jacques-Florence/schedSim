/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_DISCIPLINE_BUILDER_HELPER
#define RL_DISCIPLINE_BUILDER_HELPER


#include <cstddef>
#include <memory>
#include <vector>

namespace Mdp
{
	class Builder;
}

namespace Scheduler
{
	class Process;
}

namespace RlScheduler
{

class Configuration;

class RlDisciplineBuilderHelper
{
public:
	static void addActions(Mdp::Builder *builder);
	static void addStates(Mdp::Builder *builder, std::shared_ptr<Configuration> conf);
	static void addTaskStates(Mdp::Builder *builder);
	static void addTimeStates(Mdp::Builder *builder, std::shared_ptr<Configuration> conf);
	static bool useTimeStates(std::shared_ptr<Configuration> conf);
	static void addTemperatureStates(Mdp::Builder *builder, std::shared_ptr<Configuration> conf);
	static bool useTemperatureStates(std::shared_ptr<Configuration> conf);
	static size_t getNbOfTasks();
	static double lcm(std::vector<std::shared_ptr<Scheduler::Process>>);
};

}

#endif
