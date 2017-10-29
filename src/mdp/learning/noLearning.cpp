/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "noLearning.h"

#include <mdp/context.h>
#include <mdp/policy.h>
#include <mdp/rewards.h>
#include <mdp/transitionMatrix.h>
#include <mdp/stateSpace.h>

using namespace Mdp;

NoLearning::NoLearning(std::shared_ptr<Context> c) : LearningStrategy(c)
{
}


void NoLearning::initializeModel()
{
	/*TODO FIXME Should we modify this ?*/
	context->policy->initializeRandomly(context->randomGenerator);
	context->matrix->initializeRandomly(context->randomGenerator);
}


void NoLearning::updateModel()
{
}




