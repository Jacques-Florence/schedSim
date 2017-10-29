/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPMODEL_H
#define MDPMODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "action.h"
#include "action_impl.h" /*FIXME this and the following should not be here...*/
#include "state.h"

namespace Mdp
{

class ActionSpace;
class ConstraintList;
struct Context;
class StateSpace;
class LearningStrategy;
class MdpConfiguration;
class Rewards;

/**@brief The main class of the MDP framework
 *
 */
class MdpModel
{
public:
	MdpModel(std::shared_ptr<StateSpace> stateSpace,
	         std::shared_ptr<ActionSpace> actionSpace,
	         std::shared_ptr<MdpConfiguration> conf);
	virtual ~MdpModel();
	/**@brief call this function first
	 */
	void init();
	/**@brief call this function at the end
	 */
	void end();
	/**@brief Returns the optimal action for the current timestep
	 */
	Action *selectAction(bool updateModel=true);
	/**@brief similar to selectAction, but without updating the model
	 * @sa MdpModel::selectAction
	 */
	Action *selectActionWithoutUpdate();

	/*Ideally we don't need to know about state and actions apart from what the builder easily provide*/
	void setConstraintList(std::shared_ptr<ConstraintList> list); //not very good... but necessary?
	void setRewards(std::shared_ptr<Rewards> rewards); //not very good... but necessary?

	/** @brief Print reports to file.
	 *
	 * Prints the content of the transition matrix,
	 * the policy table, and a summary, each in its own file
	 * @folder the folder in which those files should be written
	 */
	void printReportsToFile(std::string folder);
	void printSummary(std::ostream& stream);
	void printPolicy(std::ostream& stream);
protected:
	virtual void constructContext(std::shared_ptr<StateSpace> stateSpace,
                              std::shared_ptr<ActionSpace> actionSpace,
                              std::shared_ptr<MdpConfiguration> conf);
	virtual void setLearningStrategy();
	std::shared_ptr<Context> context;
	LearningStrategy *learningStrategy{nullptr};
	void record(state_t state, action_t action, double reward);

	std::vector<state_t> stateHistory;
	std::vector<action_t> actionHistory;
	std::vector<double> rewardHistory;
	bool recordHistory{false};
};


}
#endif
