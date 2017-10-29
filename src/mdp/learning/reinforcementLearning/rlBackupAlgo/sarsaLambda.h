/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SARSA_LAMBDA_H
#define SARSA_LAMBDA_H

#include "eligibilityTraceAlgo.h"

namespace Mdp
{

class SarsaLambda : public EligibilityTraceAlgo
{
public:
	static constexpr const char *configKey = "sarsaLambda";
public:
	SarsaLambda(std::shared_ptr<Context> c, TabularActionValues *av)
		: EligibilityTraceAlgo(c, av)
		, tabularAv(av)
		{};
	virtual void updateActionValues(state_t previousState, state_t nextState, action_t previousAction, double reward);
private:
	TabularActionValues *tabularAv{nullptr};
};


}

#endif
