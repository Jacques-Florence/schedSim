/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef DELAYED_Q_LEARNING_H
#define DELAYED_Q_LEARNING_H

#include "eligibilityTraceAlgo.h"
#include <mdp/learning/reinforcementLearning/actionValuesFunction/tabularActionValues.h>

namespace Mdp
{

/**Note: this is not an eligibility trace algorithm, but it is here for testing purposes
*/
class DelayedQLearning : public EligibilityTraceAlgo
{
public:
	static constexpr const char *configKey = "delayedQLearning";
public:
	DelayedQLearning(std::shared_ptr<Context> c, TabularActionValues *av) : EligibilityTraceAlgo(c, av){};
	virtual void updateActionValues(state_t previousState, state_t nextState, action_t previousAction, double reward);
};


}

#endif
