/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "builder.h"

using namespace Mdp;

Builder::Builder(std::shared_ptr<DomainModel> model)
{
	aBuilder.setDomainModel(model);
	sBuilder.setDomainModel(model);
}

void Builder::addAction(Action *action)
{
	aBuilder.addAction(action);
}

std::shared_ptr<ActionSpace> Builder::getActionSpace()
{
	return aBuilder.getActionSpace();
}

void Builder::addPriorityState(PriorityState *state)
{
	sBuilder.addPriorityState(state);
}

void Builder::addDimension(StateSpaceDimension *dim)
{
	sBuilder.addDimension(dim);
}

std::shared_ptr<StateSpace> Builder::getStateSpace()
{
	return sBuilder.getStateSpace();
}

void Builder::addActionDimension(ActionDimension *dim)
{
	aBuilder.addActionDimension(dim);
}
