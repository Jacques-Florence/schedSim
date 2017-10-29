/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ELIGIBILITY_TRACE_ALGO_H
#define ELIGIBILITY_TRACE_ALGO_H

#include "rlBackupAlgorithm.h"
#include <mdp/learning/reinforcementLearning/actionValuesFunction/tabularActionValues.h>

namespace Mdp
{

class EligibilityTraceAlgo : public RlBackupAlgorithm
{
public:
	EligibilityTraceAlgo(std::shared_ptr<Context> c, TabularActionValues *av)
		: RlBackupAlgorithm(c, av)
		, tabularAv(av)
		{};
	virtual void init();
	virtual void end();
	virtual void updateActionValues(state_t previousState, state_t nextState, action_t previousAction, double reward)=0;
protected:
	void updateState(state_t previousState, action_t previousAction, double reward);
	TabularActionValues *tabularAv{nullptr};
	state_t previousPreviousState{0};
	action_t previousPreviousAction{0};
	double previousReward{0.0};
	std::vector<std::vector<double>> e;
	double lambda{0.5};
	double discountFactor{0.5};
	size_t stateSize{0};
	size_t actionSize{0};
};


}

#endif
