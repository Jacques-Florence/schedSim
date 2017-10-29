/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlDisciplineBuilder.h"

#include <cassert>
#include <iostream>
#include <memory>

#include <utils/math.h>

#include <scheduler/process.h>
#include <scheduler/queue.h>
#include <scheduler/system.h>

#include <mdp/mdpModel.h>
#include <mdp/mdpConfiguration.h>
#include <mdp/builder.h>
#include <mdp/actionDimension.h>

#include "configuration.h"
#include "actions.h"
#include "domainModel.h"
#include "stateDimensions/taskDimensions.h"
#include "stateDimensions/timeDimension.h"
#include "stateDimensions/temperatureDimension.h"

using namespace RlScheduler;

void RlDisciplineBuilder::buildRlDisciplineModels(RlDiscipline *disc)
{
	disc->model = std::make_shared<DomainModel>(std::dynamic_pointer_cast<Configuration>(disc->conf));
	disc->model->readyQueue = Scheduler::Queue::getReadyQueue();
	disc->model->running = nullptr;

	Mdp::Builder builder(disc->model);
	RlDisciplineBuilderHelper::addActions(&builder);
	RlDisciplineBuilderHelper::addStates(&builder, std::dynamic_pointer_cast<Configuration>(disc->conf));	
	disc->mdpConf = std::make_shared<Mdp::MdpConfiguration>(disc->conf->getName());

	/*FIXME for conf param, why not use RlSchedulerConfiguration, and have that inherit from MdpConfig.
	I tried to do that, but it becomes a big mess. See the git branch configurationMess*/
	disc->mdpModel = new Mdp::MdpModel(builder.getStateSpace(),
	                                   builder.getActionSpace(),
	                                   disc->mdpConf);
}








