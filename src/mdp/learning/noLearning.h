/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NOLEARNING_H
#define NOLEARNING_H

#include "learningStrategy.h"

namespace Mdp
{

struct Context;

class NoLearning : public LearningStrategy
{
public:
	static constexpr const char *configKey = "noLearning";
public:
	NoLearning(std::shared_ptr<Context> context);
	void updateModel();
	void initializeModel();
private:
};


}
#endif
