/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTION_DIMENSION_H
#define ACTION_DIMENSION_H

#include <vector>

namespace Mdp
{

class Action;

class ActionDimension
{
public:
	void addAction(Action *);
	std::vector<Action*> getActionList(); /*FIXME: DO NOT USE*/
	Action *getAction(int index);
	int getNumberOfActions();
private:
	std::vector<Action*> actions;
};


}

#endif


