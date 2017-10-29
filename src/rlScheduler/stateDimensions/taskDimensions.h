/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_SCHEDULER_TASK_DIMENSIONS
#define RL_SCHEDULER_TASK_DIMENSIONS

#include <mdp/stateSpaceDimension.h>


namespace RlScheduler
{

class DomainModel;

class TaskDimension : public Mdp::StateSpaceDimension
{
public:
	TaskDimension(int pid);
	std::string getName() override;
	/**
	 * @return 1 if the process is in the ready queue, 0 otherwise
	 */
	Mdp::statePosition_t getPosition() override;
	size_t getNumberOfPositions() override;
private:
	std::shared_ptr<DomainModel> model{nullptr};
	int pid;
};

}

#endif
