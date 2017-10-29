/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "actionSpaceBuilder.h"

#include <stdexcept>

#include <utils/counter.h>

#include "action.h"
#include "actionSpace.h"
#include "actionDimension.h"
#include "complexAction.h"

using namespace Mdp;

std::shared_ptr<ActionSpace> ActionSpaceBuilder::getActionSpace()
{
	if (domainModel == nullptr) /*FIXME domainModel is a shared_ptr*/
	{
		throw std::runtime_error("Domain model not set");
	}
	std::shared_ptr<ActionSpace> space(new ActionSpace);
	space->domainModel = domainModel;
	std::vector<Action*> actionVector;
	if (dimensions.size() == 0)
	{
		actionVector = actions;
	}
	else
	{
		long long int nbActions = actionDimensionCounter.getNumberOfValues();	
		actionDimensionCounter.initialize();
		std::vector<unsigned int> counterValue;
		for (long long int i = 0; i < nbActions; i++)
		{
			ComplexAction *complexAction = new ComplexAction;
			counterValue = actionDimensionCounter.getValue();
			for (unsigned int j = 0; j < dimensions.size(); j++)
			{
				Action *action = dimensions[j]->getAction(counterValue[j]);
				action->domainModel = domainModel; /*TODO: this is very ugly*/
				complexAction->actions.push_back(action);
			}
			actionVector.push_back(complexAction);
			actionDimensionCounter.increment();
		}
	}
	space->actions = actionVector;
	space->setDomainModelOfActions(); /*TODO: can we do better?*/
	return space;
}

void ActionSpaceBuilder::addAction(Action *action)
{
	actions.push_back(action);
}



void ActionSpaceBuilder::setDomainModel(std::shared_ptr<DomainModel> model)
{
	domainModel = model;
}

void ActionSpaceBuilder::addActionDimension(ActionDimension *dim)
{
	dimensions.push_back(dim);
	actionDimensionCounter.addWheel(dim->getNumberOfActions());
}
