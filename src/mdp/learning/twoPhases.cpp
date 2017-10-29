/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "twoPhases.h"

#include <mdp/context.h>
#include <mdp/mdpConfiguration.h>

#include "matrixLearning.h"
#include "noLearning.h"
#include "solver.h"

using namespace Mdp;

TwoPhases::TwoPhases(std::shared_ptr<Context> c) : LearningStrategy(c)
{
}


TwoPhases::~TwoPhases()
{
	delete learning;
	delete acting;
}


void TwoPhases::initializeModel()
{
	learning = new MatrixLearning(context);
	acting = new NoLearning(context);
	learning->initializeModel();
	acting->initializeModel();
}


void TwoPhases::updateModel()
{
	if (count < learningIterations)
	{
		count++;
		learning->updateModel();
	}
	if (count == learningIterations)
	{
		Solver *solver = context->conf->getSolverFromFile();
		/*FIXME: remove the .get()s and use shared pointers everywhere*/
		solver->solve(context->policy.get(), context->rewards.get(), context->constraintList.get(), context->matrix.get(), context->horizon.get());
	}
	if (count > learningIterations)
	{
		acting->updateModel(); /*this supposedly does nothing*/
	}
}

