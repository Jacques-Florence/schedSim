/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef COMPLEX_ACTION_H
#define COMPLEX_ACTION_H

#include <vector>
#include "action.h"

namespace Mdp
{


class ComplexAction : public Action
{
friend ActionSpaceBuilder;
public:
	~ComplexAction();
	std::string getName();
	void performAction();
protected:
	/*This vector is initialized by our friend ActionSpaceBuilder*/
	std::vector<Action*> actions;
};




}



#endif
