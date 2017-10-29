/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTIONSPACE_H
#define ACTIONSPACE_H

#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "action_impl.h"
#include "actionDimension.h"

namespace Mdp
{

class Action;
class ActionSpaceBuilder;
class DomainModel;
class MdpModel;


class ActionSpace
{
	friend ActionSpaceBuilder;
	friend MdpModel;
public:
	virtual size_t size();
	~ActionSpace();
	Action *getAction(action_t action);
	void updateLastAction(action_t a);
	action_t getLastAction();
protected:
	ActionSpace();
	void setDomainModelOfActions();

	std::vector<Action*> actions;
	std::shared_ptr<DomainModel> domainModel{nullptr};
	action_t lastAction{0};
	std::vector<ActionDimension> dimensions;
};

}
#endif
