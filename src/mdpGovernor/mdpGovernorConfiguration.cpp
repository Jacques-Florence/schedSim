/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "mdpGovernorConfiguration.h"

#include <string>

#include "mdpGovernor.h"
#include "schedulerDimensions.h"

using namespace MdpGov;

Scheduler::FreqGovernor *MdpGovernorConfiguration::getFreqGovernorFromFile()
{
	Scheduler::FreqGovernor *governor = Scheduler::SchedulerConfiguration::getFreqGovernorFromFile();
	if (governor == nullptr)
	{
		std::string value = getStringValue("scheduler", "governor");
		if (!value.compare(MdpGovernor::configKey))
			return (new MdpGovernor);
	}
	return governor;
}

std::vector<Mdp::StateSpaceDimension*> MdpGovernorConfiguration::getDimensionsFromFile()
{
	std::vector<Mdp::StateSpaceDimension*> vect;
	std::vector<std::string> values = getStringList("mdpGovernor", "dimensions");
	for (size_t i = 0; i < values.size(); i++)
	{
		if (!values[i].compare(ReadyQueueDimension::configKey))
		{
			vect.push_back(new ReadyQueueDimension);
		}
		else if (!values[i].compare(WaitQueueDimension::configKey))
		{
			vect.push_back(new WaitQueueDimension);
		}
		else if (values[i].compare(FrequencyDimension::configKey))
		{
			vect.push_back(new FrequencyDimension);
		}
		else if (values[i].compare(TemperatureDimension::configKey))
		{
			vect.push_back(new TemperatureDimension);
		}
		else if (values[i].compare(MissRateDimension::configKey))
		{
			vect.push_back(new MissRateDimension);
		}
	}
	return vect;
}




