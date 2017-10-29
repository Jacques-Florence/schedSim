/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MATRIXLEARNING_H
#define MATRIXLEARNING_H

#include <vector>

#include <mdp/action_impl.h>
#include <mdp/state.h>
#include "learningStrategy.h"

namespace Mdp
{
struct Context;

class MatrixLearning : public LearningStrategy
{
public:
	static constexpr const char *configKey = "matrixLearning";
public:
	MatrixLearning(std::shared_ptr<Context> context);
	void initializeModel();
	void updateModel();
private:
	void updateMatrix();
	
	state_t previousState;
	action_t previousAction;
	std::vector<std::vector<std::vector<int>>> occurences;
	int nbOfUpdates{0};
};


}







#endif
