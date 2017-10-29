/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <vector>

namespace Utils{class RandomGenerator;}

namespace Mdp
{

class ConstraintList;
class Policy;
class Rewards;
class TransitionMatrix;
class StateSpace;
class ActionSpace;
class MdpConfiguration;
struct Horizon;


struct Context
{
	std::shared_ptr<Policy> policy;
	std::shared_ptr<Rewards> rewards;
	std::shared_ptr<ConstraintList> constraintList;
	std::shared_ptr<TransitionMatrix> matrix;
	std::shared_ptr<StateSpace> stateSpace;
	std::shared_ptr<ActionSpace> actionSpace;
	std::shared_ptr<Utils::RandomGenerator> randomGenerator;
	std::shared_ptr<MdpConfiguration> conf;
	std::shared_ptr<Horizon> horizon;
};



}
#endif
