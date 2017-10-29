/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TWOPHASES_H
#define TWOPHASES_H

#include "learningStrategy.h"


namespace Mdp
{
struct Context;


class TwoPhases : public LearningStrategy
{
public:
	static constexpr const char *configKey = "twoPhases";
public:
	TwoPhases(std::shared_ptr<Context> context);
	~TwoPhases();
	void initializeModel();
	void updateModel();
protected:
	int count{0};
	const int learningIterations{100};
	LearningStrategy *learning;
	LearningStrategy *acting;
};

}

#endif
