/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_BACKUP_ALGORITHM_H
#define RL_BACKUP_ALGORITHM_H

#include <vector>
#include <utility>

#include <mdp/state.h>
#include <mdp/action_impl.h>
#include <mdp/stateSpace.h>
#include <mdp/actionSpace.h>
#include <mdp/learning/reinforcementLearning/actionValuesFunction/actionValuesFunction.h>

namespace Utils
{
	class RandomGenerator;
}

namespace Mdp
{
struct Context;

class RlBackupAlgorithm
{
public:
	RlBackupAlgorithm(std::shared_ptr<Context> c, ActionValuesFunction *av);
	virtual ~RlBackupAlgorithm(){};
	virtual void init() = 0;
	virtual void updateActionValues(state_t previousState,
	                                state_t nextState,
	                                action_t previousAction,
	                                double reward) = 0;
	virtual void end()=0;

	/*FIXME: first of all, this is only valid for tabular AVs.
	Also, the notifyUpdateNeeded thing is bad design.
	Also, do they need to be public?*/
	virtual double getMaxQ(state_t state);
	virtual std::pair<action_t, double> getBestActionAndQ(state_t state);
	virtual action_t getBestAction(state_t state);
	virtual void updateBestActionAndQ(state_t state);
	virtual void notifyUpdateNeeded();
protected:
	std::shared_ptr<Context> context{nullptr};
	ActionValuesFunction *actionValues{nullptr};
	double alpha{-1.0};
	double alpha0{0.1};
	double alphaCounter{1.0};
	double alphaDecaySpeed{1.0};
	bool hyperbolic{false};
	bool stepwise{false};
	unsigned long long stepwiseCounter{0};
	unsigned long long int stepLength{0};
	virtual void initAlpha();
	virtual void updateAlpha();
	std::vector<double> bestQ;
	std::vector<action_t> bestAction;
	std::vector<bool> needsUpdate;
	virtual void updateIfNeeded(state_t state);
};


}




#endif
