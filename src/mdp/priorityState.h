/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef PRIORITYSTATE_H
#define PRIORITYSTATE_H


#include <memory>
#include <string>

namespace Mdp
{


class DomainModel;
class StateSpacBuilder;
class StateSpace;

/**@brief a single state of the state space

 * This class should be used to model states that do not belong to dimensions.
 * The qualifier of "priority" comes from the fact that, when determining the current state, the framework first checks if the system is in any of the priority states,
 * and if not, only then will determine what position the system has in the "dimensioned" part of the state space.
 */
class PriorityState
{
friend StateSpaceBuilder;
friend StateSpace;
public:
	virtual ~PriorityState(){};
	/**@brief returns the name of that state
	 */
	virtual std::string getName()=0;
	/**@brief Given the information provided by the DomainModel, this function checks if the system is in that state.
	 * @return returns true if the system is in this state, or false otherwise
	 */
	virtual bool isInState()=0;
protected:
	template<typename T>
	std::shared_ptr<T> getModel()
	{
		std::shared_ptr<T> model = std::dynamic_pointer_cast<T>(domainModel);
		if (model == nullptr)
			throw std::runtime_error("inconsistent domain model type");
		return model;
	}
	std::shared_ptr<DomainModel> domainModel{nullptr};
};

}







#endif




