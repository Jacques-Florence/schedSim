/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "actionSpace.h"

#include <cassert>

#include "action.h"

using namespace Mdp;


ActionSpace::ActionSpace()
{

}

ActionSpace::~ActionSpace()
{
	for (size_t i = 0; i < actions.size(); i++)
	{
		delete actions[i];
	}
}

size_t ActionSpace::size()
{
	return actions.size();
}


void ActionSpace::setDomainModelOfActions()
{
	for (size_t i = 0; i < actions.size(); i++)
	{
		actions[i]->domainModel = domainModel;
	}
}




Action *ActionSpace::getAction(action_t a)
{
	return actions[a];
}



void ActionSpace::updateLastAction(action_t a)
{
	lastAction = a;
}

action_t ActionSpace::getLastAction()
{
	return lastAction;
}
