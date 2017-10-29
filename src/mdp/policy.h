/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef POLICY_H
#define POLICY_H

#include <ostream>
#include <memory>
#include <string>
#include <vector>

#include "action_impl.h"
#include "state.h"

namespace Utils{class RandomGenerator;}

namespace Mdp
{

class Policy
{
public:
	Policy(int nbOfStates, int nbOfActions, std::shared_ptr<Utils::RandomGenerator> gen);
	void update(state_t state, const std::vector<double> &vector);
	action_t getAction(state_t state);
	void initializeUniformly();
	void initializeRandomly(std::shared_ptr<Utils::RandomGenerator> gen);
	void initializeFromFile(std::string filename);
	void saveToFile(std::string filename);
	void print(std::ostream& stream);
	size_t getNbOfStates();
	size_t getNbOfActions();
protected:
	std::vector<double> *getActionVector(state_t state);//this is a ptr for performance reasons
	std::vector<std::vector<double>> policy; //policies are stochastic
	size_t nbOfStates;
	size_t nbOfActions;
	std::shared_ptr<Utils::RandomGenerator> randomGenerator;
	void handleErrorInGettingAction(std::vector<double> *vector, state_t state, double d);
};




}




#endif



















