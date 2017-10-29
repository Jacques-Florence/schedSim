/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "matrixLearning.h"

#include <mdp/action_impl.h>
#include <mdp/actionSpace.h>
#include <mdp/context.h>
#include <mdp/policy.h>
#include <mdp/rewards.h>
#include <mdp/stateSpace.h>
#include <mdp/transitionMatrix.h>

using namespace Mdp;

MatrixLearning::MatrixLearning(std::shared_ptr<Context> c) : LearningStrategy(c)
{
	size_t S = c->stateSpace->size();
	size_t A = c->actionSpace->size();
	occurences = std::vector<std::vector<std::vector<int>>>(S, 
		std::vector<std::vector<int>>(A, std::vector<int>(S, 0)));
}


void MatrixLearning::initializeModel()
{
	context->policy->initializeRandomly(context->randomGenerator);
	context->matrix->initializeRandomly(context->randomGenerator);
	previousState = context->stateSpace->getState();
}

void MatrixLearning::updateModel()
{
	context->policy->initializeRandomly(context->randomGenerator);//take a random action everytime
	state_t state = context->stateSpace->getState();

	if (nbOfUpdates != 0)
		occurences[previousState][previousAction][state]++;

	nbOfUpdates++;

	previousState = state;
	previousAction = context->policy->getAction(previousState);
	updateMatrix(); //not very efficient to do that here every time
}


void MatrixLearning::updateMatrix()
{
	size_t S = context->stateSpace->size();
	size_t A = context->actionSpace->size();
	for (state_t i = 0; i < S; i++)
	{
		for (action_t j = 0; j < A; j++)
		{
			double N = 0;
			for (state_t k = 0; k < S; k++)
			{
				N += (double) occurences[i][j][k];
			}
			for (state_t k = 0; k < S; k++)
			{
				context->matrix->set(i, k, j, ((double)occurences[i][j][k])/N);
			}
		}
	}
}



