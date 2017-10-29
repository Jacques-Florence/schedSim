/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTION_VALUES_FUNCTION_H
#define ACTION_VALUES_FUNCTION_H

#include <mdp/state.h>
#include <mdp/action_impl.h>
#include <vector>
#include <memory>

namespace Mdp
{

struct Context;

/**
 * This is the interface for any function
 * mapping a (state, action) paitr to an action value
 */
class ActionValuesFunction
{
public:
	/**Get the action value for a given state and action
	 */
	virtual double getValue(state_t state, action_t action)=0;
	/**Get the vector of action values for all actions for a given state
	 */
	virtual std::vector<double> getValues(state_t state)=0;
protected:
};

}

#endif
