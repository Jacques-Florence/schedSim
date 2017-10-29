/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "complexAction.h"

#include <sstream>

using namespace Mdp;



ComplexAction::~ComplexAction()
{
	for (size_t i = 0; i < actions.size(); i++)
	{
		//delete actions[i]; 
	}
}

std::string ComplexAction::getName()
{
	std::stringstream str;
	str << "Complex action performing the following:\n";
	for (size_t i = 0; i < actions.size(); i++)
	{
		str << "." << actions[i]->getName() << "\n";
	}
	return str.str();
}


void ComplexAction::performAction()
{
	for (size_t i = 0; i < actions.size(); i++)
	{
		actions[i]->performAction();
	}
}



