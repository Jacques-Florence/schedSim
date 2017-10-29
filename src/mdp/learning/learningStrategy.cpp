/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "learningStrategy.h"

#include <mdp/context.h>
#include <mdp/policy.h>
#include <mdp/rewards.h>
#include <mdp/transitionMatrix.h>


using namespace Mdp;

LearningStrategy::LearningStrategy(std::shared_ptr<Context> c) : context(c)
{
}

LearningStrategy::~LearningStrategy()
{
}


