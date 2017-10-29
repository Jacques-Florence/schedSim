/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTION_SELECTION_STRATEGY_H
#define ACTION_SELECTION_STRATEGY_H

#include <vector>

#include <mdp/actionSpace.h>

namespace Mdp
{

class ActionSelectionStrategy
{
public:
	/**Generate the policy from the vector of action values (given a given state)
	 */
	virtual std::vector<double> generatePolicy(const std::vector<double>&, action_t bestAction)=0;
};

}

#endif /*ACTION_SELECTION_STRATEGY_H*/
