/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDP_STATE_SPACE_H
#define MDP_STATE_SPACE_H

#include <memory>
#include <vector>

#include "action_impl.h"
#include "state.h"
#include "stateSpaceDimension.h"


namespace Mdp
{

typedef std::vector<statePosition_t> StateInternal;

class DomainModel;
class PriorityState;

class StateSpace
{
	friend class StateSpaceBuilder;
public:
	StateSpace(const StateSpace&) = delete;
	StateSpace& operator=(const StateSpace&) = delete;

	~StateSpace();
	virtual size_t size();
	virtual state_t getState();
	/** 
	 * The only reason why getState and updateCurrentState
	 * are two different functions is for performance
	 */
	virtual void updateCurrentState();
	/**Return the immediate reward corresponding to the current state
	 */
	virtual double getReward();
	/**Returns the number of dimensions in the state space
	 */
	virtual size_t getNbOfDimensions();
	/**Returns the state as a factorized vector: one element for each dimension
	 */
	virtual std::vector<size_t> *factorize(state_t state);
	/**Returns for each state dimension, the number of positions
	 */
	virtual std::vector<size_t> getDimensionSizes();
protected:
	StateSpace(){};
	/**This returns the state in the part of the state space that has dimensions.
	 * If the current state is actually a priority state,
	 * this value is not the real current state.
	 */
	void updateInternalState();
	int getPriorityStateInternal();
	/*state space has to be constructed with the builder*/
	StateSpace(size_t nbOfStates, size_t nbOfPriorityStates,
		std::vector<StateSpaceDimension *> dimensions,
		std::vector<PriorityState *> priorityStates);
	state_t convertState(StateInternal);

	size_t nbOfStates{0}; /*excluding priority states*/
	size_t nbOfPriorityStates{0};
	std::vector<StateSpaceDimension *> dimensions;
	std::vector<PriorityState *> priorityStates;
	StateInternal currentState;
	std::shared_ptr<DomainModel> domainModel{nullptr};
	state_t currentExternalState{0};

	StateInternal internalState;

};





}




#endif
