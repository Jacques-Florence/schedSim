/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTIONSPACEBUILDER_H
#define ACTIONSPACEBUILDER_H

#include <memory>
#include <vector>

#include <utils/counter.h>

namespace Mdp
{

class Action;
class ActionSpace;
class ActionDimension;
class DomainModel;

/**@brief Builds the action space
 */
class ActionSpaceBuilder
{
public:
	/**@brief sets the domain model used by the actions to act on the environment
	 * @param model a pointer to the domain model
	 * @sa DomainModel
	 */
	void setDomainModel(std::shared_ptr<DomainModel> model);
	/**@brief add an action to the actino space
	 * @param action the action to add
	 * @sa Action
	 */
	void addAction(Action *action);
	/**@brief get the action space
	 * @return the action space to be given to the MdpModel constructor
	 * @sa MdpModel
	 */
	std::shared_ptr<ActionSpace> getActionSpace();
	/**
	 */
	void addActionDimension(ActionDimension*);
private:
	std::vector<Action*> actions;
	std::shared_ptr<DomainModel> domainModel;
	std::vector<ActionDimension*> dimensions;
	Utils::Counter actionDimensionCounter;
};

}


#endif
