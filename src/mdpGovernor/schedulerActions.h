/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SCHEDULERACTIONS_H
#define SCHEDULERACTIONS_H


#include <memory>
#include <string>

#include <mdp/action.h>

#include "schedulerDomainModel.h"

namespace Scheduler
{
	class System;
	class Processor;
	class Queue;
}

namespace MdpGov
{

class SetMinFreq : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() override;
};

class SetMaxFreq : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() override;
};

}
#endif
