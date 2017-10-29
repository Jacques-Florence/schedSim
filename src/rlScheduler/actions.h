/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RL_SCHEDULER_ACTIONS_H
#define RL_SCHEDULER_ACTIONS_H

#include <memory>

#include <mdp/action.h>


namespace Scheduler
{
	class Process;
}


namespace RlScheduler
{

class Action : public Mdp::Action
{
public:
	/**
	 * @param processId is the ID of the process to be run when this action is selected
	 */
	Action(int processId);
	void performAction() override;
	std::string getName() override;
	/**@brief returns the process to run according to the RL algorithm
	 * @return returns null if the process is not available in the ready queue, and also not running.
	 * In case several jobs of the same task are runnable, and if one of them is currently running,
	 * the job currently running is given priority. Otherwise, no guarantee iis made about which of the
	 * jobs is selected.
	 */
	virtual std::shared_ptr<Scheduler::Process> getProcessToRun();
protected:
	Action(){};
	int id;
};


class SleepAction : public Action
{
public:
	SleepAction();
	SleepAction(int);
	void performAction() override;
	std::string getName() override;
	std::shared_ptr<Scheduler::Process> getProcessToRun() override;
};


}


#endif
