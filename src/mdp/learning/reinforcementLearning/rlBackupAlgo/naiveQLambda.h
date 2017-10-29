/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NAIVE_Q_LAMBDA_H
#define NAIVE_Q_LAMBDA_H

#include "eligibilityTraceAlgo.h"

namespace Mdp
{

class NaiveQLambda : public EligibilityTraceAlgo
{
public:
	static constexpr const char *configKey = "naiveQLambda";
public:
	NaiveQLambda(std::shared_ptr<Context> c, TabularActionValues *av)
		: EligibilityTraceAlgo(c, av)
		, tabularAv(av)
		{};
	virtual void updateActionValues(state_t previousState, state_t nextState, action_t previousAction, double reward);
private:
	TabularActionValues *tabularAv{nullptr};
};

}

#endif
