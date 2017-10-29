/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "mdpConfiguration.h"

#include <stdexcept>

#include "context.h"
#include "horizon.h"
#include "learning/linearProgramming.h"
#include "learning/matrixLearning.h"
#include "learning/noLearning.h"
#include "learning/reinforcementLearning/reinforcedLearning.h"
#include "stateSpaceDimension.h"
#include "learning/twoPhases.h"


using namespace Mdp;


LearningStrategy *MdpConfiguration::getLearningStrategyFromFile(std::shared_ptr<Context> context)
{
	std::string value = getStringValue("mdp", "learningStrategy");
	if (!value.compare(MatrixLearning::configKey))
		return (new MatrixLearning(context));
	if (!value.compare(NoLearning::configKey))
		return (new NoLearning(context));
	if (!value.compare(ReinforcedLearning::configKey))
		return (new ReinforcedLearning(context));
	if (!value.compare(TwoPhases::configKey))
		return (new TwoPhases(context));
	return nullptr;
}




Solver *MdpConfiguration::getSolverFromFile()
{
	std::string value = getStringValue("mdp", "solver");
	if (!value.compare(LinearProgramming::configKey))
		return (new LinearProgramming(this));
	return nullptr;
		
}



std::shared_ptr<Horizon> MdpConfiguration::getHorizonFromFile()
{
	std::shared_ptr<Horizon> horizon = std::make_shared<Horizon>();
	horizon->discountFactor = getDoubleValue("mdp", "discountFactor");


	std::string value = getStringValue("mdp","costHorizon");
	if (!value.compare("average"))
	{
		if (horizon->discountFactor < 1.0 || horizon->discountFactor > 1.0)
		{
			/*TODO: use the logging module and write it in orange*/
			std::cout << "Warning: using a discount factor of 1.0 instead of ";
			std::cout << horizon->discountFactor << "\n";
		}
		horizon->discountFactor = 1.0;
		horizon->finiteHorizon = false;
	}
	else if (!value.compare("discounted"))
	{
		horizon->finiteHorizon = false;
	}
	else if (!value.compare("finite"))
	{
		horizon->finiteHorizon = false;
	}
	else
	{
		throw std::runtime_error("unknown horizon type");
	}

	return horizon;
}


double MdpConfiguration::getRlEpsilonFromFile()
{
	return getDoubleValue("reinforcementLearning","epsilon");
}
