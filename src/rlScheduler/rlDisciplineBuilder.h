/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_DISCIPLINE_BUILDER_H
#define RL_DISCIPLINE_BUILDER_H


#include "rlDiscipline.h"
#include "rlDisciplineBuilderHelper.h"

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

class RlDisciplineBuilder
{
public:
	static void buildRlDisciplineModels(RlDiscipline *discipline);
};

}

#endif
