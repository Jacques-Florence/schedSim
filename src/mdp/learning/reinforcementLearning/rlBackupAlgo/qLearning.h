/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <utils/configuration.h>
#include <mdp/learning/reinforcementLearning/actionValuesFunction/tabularActionValues.h>
#include "rlBackupAlgorithm.h"



namespace Mdp
{
struct Context;

class QLearning : public RlBackupAlgorithm
{
public:
	static constexpr const char *configKey = "QLearning";
public:
	QLearning(std::shared_ptr<Context> context, TabularActionValues *actionValues);
	void init() override;
	void updateActionValues(state_t previousState,
	                        state_t nextState,
	                        action_t previousAction,
	                        double reward) override;
	void end() override;
private:
	TabularActionValues *tabularAv{nullptr};
	double discountFactor{0.5};

};

}
#endif
