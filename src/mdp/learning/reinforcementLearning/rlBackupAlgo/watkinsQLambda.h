/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef WATKINS_Q_LAMBDA_H
#define WATKINS_Q_LAMBDA_H


#include "eligibilityTraceAlgo.h"

namespace Mdp
{


class WatkinsQLambda : public EligibilityTraceAlgo
{
public:
	static const constexpr char *configKey = "watkinsQLambda";
public:
	WatkinsQLambda(std::shared_ptr<Context> c, TabularActionValues *av)
		: EligibilityTraceAlgo(c, av)
		, tabularAv(av)
		{};
	virtual void updateActionValues(state_t previousState, state_t mextState, action_t previousAction, double reward);
private:
	std::pair<double, action_t> watkinsBestQ(state_t state, action_t nextAction);
	TabularActionValues *tabularAv{nullptr};
};

}


#endif
