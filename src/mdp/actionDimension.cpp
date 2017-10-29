/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "actionDimension.h"

using namespace Mdp;

int ActionDimension::getNumberOfActions()
{
	return actions.size();
}


void ActionDimension::addAction(Action *a)
{
	actions.push_back(a);
}

std::vector<Action*> ActionDimension::getActionList()
{
	return actions;
}


Action *ActionDimension::getAction(int index)
{
	return actions[index];
}





