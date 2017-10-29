/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_DISCIPLINE_H
#define RL_DISCIPLINE_H

#include <memory>

#include <scheduler/discipline/schedulingDiscipline.h>


namespace Scheduler
{
	class Process;
	class Queue;
}

namespace Mdp
{
	class MdpModel;
	class MdpConfiguration;
}

namespace RlScheduler
{

class DomainModel;
class RlDisciplineBuilder;
class Configuration;

class RlDiscipline : public Scheduler::SchedulingDiscipline
{
friend RlDisciplineBuilder;
public:
	static constexpr const char *configKey = "rlDiscipline";
public:
	RlDiscipline(std::shared_ptr<Configuration> conf);
	~RlDiscipline();
	std::shared_ptr<Scheduler::Process> selectNextTask(Scheduler::Queue *readyQueue,
		std::shared_ptr<Scheduler::Process> running, unsigned int deadlineMisses);
	bool preempts(Scheduler::TriggeringEvent trigger);
	std::string getName(){return "Reinforcement learning real-time discipline";};
	void end() override;
private:
	void construct();
	void updateReward();
	std::shared_ptr<DomainModel> model;
	Mdp::MdpModel *mdpModel{nullptr};
	unsigned int previousDeadlineMisses{0};
	unsigned int currentDeadlineMisses{0};
	std::shared_ptr<Mdp::MdpConfiguration> mdpConf; /*FIXME*/
};


}
#endif
