/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef NEURO_Q_H
#define NEURO_Q_H

#include <vector>
#include <utils/configuration.h>
#include <mdp/learning/reinforcementLearning/actionValuesFunction/neuralNetwork.h>
#include "rlBackupAlgorithm.h"


namespace Mdp
{

struct Context;

class NeuroQ : public RlBackupAlgorithm
{
public:
	static constexpr const char *configKey = "neuroQ";
public:
	NeuroQ(std::shared_ptr<Context> context, NeuralNetwork *actionValues)
		: RlBackupAlgorithm(context, actionValues)
		, approximatedAv(actionValues)
		{};
	~NeuroQ(){};
	void init() override;
	void updateActionValues(state_t previousState
	                       ,state_t nextState
	                       ,action_t previousAction
	                       ,double reward
	                       ) override;
	void end() override;
	double getMaxQ(state_t state) override;
	std::pair<action_t, double> getBestActionAndQ(state_t state) override;
	action_t getBestAction(state_t state);
	void notifyUpdateNeeded();
private:
	double discountFactor{0.5};
	NeuralNetwork *approximatedAv{nullptr};
	size_t getNbOfStateDimensions();
	std::vector<double> getStateVector(state_t state);
	std::vector<double> generateTargetOutput(double reward, state_t previousState, state_t nextState, action_t previousAction);
	std::vector<double> generateInputVector(state_t previousState);
	double getTargetMaxQ(state_t state);
	NeuralNetwork *targetNetwork{nullptr};
	int targetUpdateInterval{5};
	void updateTargetNetwork();
};

}

#endif
