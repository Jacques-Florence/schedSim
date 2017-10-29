/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPGOVERNOR_H
#define MDPGOVERNOR_H

#include <string>
#include <scheduler/governor/freqGovernor.h>

namespace Mdp
{
	class MdpModel;
}

namespace MdpGov
{

class MdpGovernor : public Scheduler::FreqGovernor
{
public:
	static constexpr const char *configKey = "mdpGovernor";
public:
	MdpGovernor();
	virtual ~MdpGovernor();
	virtual void updateFreq(Scheduler::Processor *proc, Scheduler::Queue *readyQueue);
	virtual bool freqChangeEvent(Scheduler::TriggeringEvent trigger);
	virtual std::string getName();
	virtual void printReport(std::string folder) override;
private:
	Mdp::MdpModel *model;
	/*TODO keep track of the MdpAction history*/
};


}

#endif
