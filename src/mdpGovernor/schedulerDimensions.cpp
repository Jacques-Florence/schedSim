/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */




#include "schedulerDimensions.h"

#include <cassert>
#include <memory>
#include <stdexcept>

#include <scheduler/queue.h>
#include <scheduler/processor.h>
#include <scheduler/system.h>

#include "schedulerDomainModel.h"

using namespace MdpGov;

std::string ReadyQueueDimension::getName()
{
	return "Ready queue dimension";
}

Mdp::statePosition_t ReadyQueueDimension::getPosition()
{
	return getModel<SchedulerDomainModel>()->readyQueue->size();
}

size_t ReadyQueueDimension::getNumberOfPositions()
{
	return getModel<SchedulerDomainModel>()->readyQueue->getMaxSize()+1;
}







std::string WaitQueueDimension::getName()
{
	return  "Wait queue dimension";	
}

Mdp::statePosition_t WaitQueueDimension::getPosition()
{
	return getModel<SchedulerDomainModel>()->waitQueue->size();
}

size_t WaitQueueDimension::getNumberOfPositions()
{
	return getModel<SchedulerDomainModel>()->waitQueue->getMaxSize()+1;
}









std::string FrequencyDimension::getName()
{
	return "Frequency dimension";
}

Mdp::statePosition_t FrequencyDimension::getPosition()
{
	size_t pos;
	static Scheduler::Processor *proc = getModel<SchedulerDomainModel>()->proc;
	if (proc->getMinFreq() >= proc->getFreq())
	{
		pos = 0;
	}
	else
	{
		pos = 1;
	}
	return pos;
}

size_t FrequencyDimension::getNumberOfPositions()
{
	return 2;
}








std::string TemperatureDimension::getName()
{
	return "Temperature dimension";
}

Mdp::statePosition_t TemperatureDimension::getPosition()
{
	return -1;
}

size_t TemperatureDimension::getNumberOfPositions()
{
	return 2;
}





std::string MissRateDimension::getName()
{
	return "Miss rate dimension";
}

Mdp::statePosition_t MissRateDimension::getPosition()
{
	return -1;
}

size_t MissRateDimension::getNumberOfPositions()
{
	return -1;
}


