/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_SCHEDULER_DOMAIN_MODEL_H
#define RL_SCHEDULER_DOMAIN_MODEL_H

#include <cmath>
#include <memory>

#include <utils/record.h>

#include <mdp/domainModel.h>

namespace Scheduler
{
	class Queue;
	class Process;
	class TemperatureModel;
}

namespace RlScheduler
{

class MaxTempEstimator;
class Configuration;

class DomainModel : public Mdp::DomainModel
{
public:
	DomainModel(std::shared_ptr<Configuration> conf);
	~DomainModel();
	void end();
	double measureReward() override;
	Scheduler::Queue *readyQueue;
	std::shared_ptr<Scheduler::Process> running;
	double reward{0.0};
protected:
	double getTemperatureCost();
	double getInstantaneousTemp();
	double getAging();
private:
	std::shared_ptr<Configuration> conf;

	double deadlineMissRewardCoeff{1.0};
	double temperatureRewardCoeff{0.0};
	double agingRewardCoeff{0.0};
	MaxTempEstimator *maxTempEstimator{nullptr};
	Utils::Record tempRecord;
	Utils::Record maxTempRecord;
	bool usingThreshold{true};
};

}

#endif
