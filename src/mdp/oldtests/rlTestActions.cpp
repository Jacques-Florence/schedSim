/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlTestActions.h"


std::string GoUp::getName()
{
	return "Go Up";
}


std::string GoDown::getName()
{
	return "Go Down";
}
std::string GoLeft::getName()
{
	return "Go Left";
}
std::string GoRight::getName()
{
	return "Go Right";
}





void GoUp::performAction()
{
	std::shared_ptr<RlTestDomainModel> model = getModel<RlTestDomainModel>();
	if (model->xpos > 0 && model->xpos < 11 && model->ypos == 0)
	{
		model->xpos = model->ypos = 0;
		return;
	}
	if (model->ypos < 3)
		model->ypos++;
}




void GoDown::performAction()
{
	std::shared_ptr<RlTestDomainModel> model = getModel<RlTestDomainModel>();
	if (model->xpos > 0 && model->xpos < 11 && model->ypos == 0)
	{
		model->xpos = model->ypos = 0;
		return;
	}
	if (model->ypos > 0)
		model->ypos--;
}


void GoLeft::performAction()
{
	std::shared_ptr<RlTestDomainModel> model = getModel<RlTestDomainModel>();
	if (model->xpos > 0 && model->xpos < 11 && model->ypos == 0)
	{
		model->xpos = model->ypos = 0;
		return;
	}
	if (model->xpos > 0)
		model->xpos--;
}


void GoRight::performAction()
{
	std::shared_ptr<RlTestDomainModel> model = getModel<RlTestDomainModel>();
	if (model->xpos > 0 && model->xpos < 11 && model->ypos == 0)
	{
		model->xpos = model->ypos = 0;
		return;
	}
	if (model->xpos < 11)
		model->xpos++;
}




