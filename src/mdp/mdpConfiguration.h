/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPCONFIGURATION_H
#define MDPCONFIGURATION_H

#include <memory>
#include <vector>
#include <utils/configuration.h>


namespace Mdp
{
class LearningStrategy;
class StateSpaceDimension;
class Solver;
class Context;
class Horizon;

class MdpConfiguration : public Utils::Configuration
{
public:
	MdpConfiguration(std::string filename) : Configuration(filename){};
	virtual LearningStrategy *getLearningStrategyFromFile(std::shared_ptr<Context> context);
	virtual double getRlEpsilonFromFile();
	
	virtual std::shared_ptr<Horizon> getHorizonFromFile();
	virtual Solver *getSolverFromFile();
};



}

#endif
