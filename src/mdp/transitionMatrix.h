/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPTRANSITIONMATRIX_H
#define MDPTRANSITIONMATRIX_H

#include <memory>
#include <ostream>
#include <vector>

#include "state.h"
#include "action_impl.h"

namespace Utils{class RandomGenerator;}

namespace Mdp
{

class TransitionMatrix
{
public:
	TransitionMatrix(int nbOfStates, int nbOfActions);
	~TransitionMatrix();
	void set(state_t from, state_t to, action_t action, double proba);
	/** Given an initial state s1 and an action a, this function returns the probability to land in state s2.
	 *
	 *  @param from the state from which we start
	 *  @param to the state in which we land
	 *  @param action the actino taken in the initial state
	 */
	double get(state_t from, state_t to, action_t action);
	/** Given an initial state s1 and an action a, this function returns the probability to land in state s2.
	 *
	 *  This function breaks hiding of implementation but makes things easier for the policy calculation... 
	 *  @param stateAndAction is s1*(size of action space) + a.
	 *  @param to the state in which we land
	 */
	double get(size_t stateAndAction, state_t to);
	void initializeRandomly(std::shared_ptr<Utils::RandomGenerator> gen);
	void print(std::ostream& stream);
private:
	double *getArray();

	double *matrix{nullptr};
	size_t nbOfStates;
	size_t nbOfActions;
};


}

#endif
