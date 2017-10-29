/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDP_GOVERNOR_CONFIGURATION_H
#define MDP_GOVERNOR_CONFIGURATION_H

#include <vector>

#include <scheduler/schedulerConfiguration.h>

namespace Mdp
{
	class StateSpaceDimension;
}

namespace MdpGov
{
class MdpGovernorConfiguration : public Scheduler::SchedulerConfiguration
{
public:
	MdpGovernorConfiguration(std::string file) : Scheduler::SchedulerConfiguration(file){};
	virtual Scheduler::FreqGovernor *getFreqGovernorFromFile() override;
	virtual std::vector<Mdp::StateSpaceDimension*> getDimensionsFromFile();
};

}

#endif
