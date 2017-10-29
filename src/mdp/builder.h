/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef BUILDER_H
#define BUILDER_H

#include "actionSpaceBuilder.h"
#include "stateSpaceBuilder.h"

namespace Mdp
{

class Builder
{
public:
	Builder(std::shared_ptr<DomainModel> domainModel);

	void addAction(Action *action);
	void addActionDimension(ActionDimension *dim);
	std::shared_ptr<ActionSpace> getActionSpace();

	void addPriorityState(PriorityState *state);
	void addDimension(StateSpaceDimension *dimension); /*TODO: rename as addStateDimension*/
	std::shared_ptr<StateSpace> getStateSpace();
private:
	ActionSpaceBuilder aBuilder;
	StateSpaceBuilder sBuilder;	
};

}

#endif
