/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef EPSILON_GREEDY_H
#define EPSILON_GREEDY_H

#include "actionSelectionStrategy.h"

namespace Mdp
{
class EpsilonGreedy : public ActionSelectionStrategy
{
public:
	EpsilonGreedy(double epsilon, double epsilonDecaySpeed, long long unsigned int epsilonTimeout);
	virtual std::vector<double> generatePolicy(const std::vector<double>&, action_t bestAction) override;
protected:
	double epsilon{0.1};
	double epsilonDecaySpeed{1.0};
	long long unsigned int epsilonTimeout{0};
	void updateEpsilon();
};
}
#endif /*EPSILON_GREEDY_H*/

