/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef REINFORCEDLEARNING_H
#define REINFORCEDLEARNING_H

#include <mdp/learning/learningStrategy.h>

#include <utility>
#include <vector>

#include <mdp/state.h>
#include <mdp/action_impl.h>

#include <utils/record.h>

#include "actionValuesFunction/tabularActionValues.h"

#include "actionSelection/actionSelectionStrategy.h"

#include "actionValuesRecord.h"

namespace Mdp
{
struct Context;
class RlBackupAlgorithm;


class ReinforcedLearning : public LearningStrategy
{
public:
	static constexpr const char *configKey = "reinforcedLearning";
public:
	ReinforcedLearning(std::shared_ptr<Context> context);
	~ReinforcedLearning();
	void initializeModel();
	void updateModel();
	void end();
protected:
	size_t S{0};
	size_t A{0};
	void initializePolicy();
	//void initializeActionValues();
	void initializeActionSelectionStrategy();
	void updatePolicy(state_t state);
	void updateLongTermReward(double reward, double discountFactor);
	void epsilonGreedyPolicyUpdate(state_t state);
	action_t getBestAction(state_t state);
	ActionValuesFunction *actionValues{nullptr};
	//double epsilon{0.1};
	double discountFactor{0.1};
	double alpha{0.1};
	double alphaDecaySpeed{0.99};
	//double epsilonDecaySpeed{0.99};
	state_t previousState;
	action_t previousAction;
	RlBackupAlgorithm *backupAlgo{nullptr};
	RlBackupAlgorithm *getBackupAlgorithm();
	//std::vector<std::vector<std::vector<double>>> actionValuesRecord;
	ActionValuesRecord actionValuesRecord;
	void printAVRecord();
	void updateEpsilon();
	long long unsigned int epsilonTimeOut{0};
	void updateActualDiscountedReward(double reward);
	double actualDiscountedReward{0.0};
	Utils::Record rewardRecord;
	void printActionValuesToFile(std::string folder);
	ActionSelectionStrategy *actionSelectionStrategy{nullptr};
	double longTermReward{0.0};
	action_t getBestActionFromInitialPolicy(state_t s);
	void printStateSpace();
};






}


#endif
