/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef STATESPACEBUILDER_H
#define STATESPACEBUILDER_H

#include <memory>
#include <vector>

namespace Mdp
{
class DomainModel;
class PriorityState;
class StateSpace;
class StateSpaceDimension;

/**@brief builds a domain specific state space
 */
class StateSpaceBuilder
{
public:
	/**@brief sets the domain model used by the state space to determine current state
	 * @sa DomainModel
	 */
	void setDomainModel(std::shared_ptr<DomainModel> model);
	/**@brief adds single states to the state space
	 * @sa PriorityState
	 */
	void addPriorityState(PriorityState *);
	/**@brief adds a dimension to the state space
	 * @sa StateSpaceDimension
	 */
	void addDimension(StateSpaceDimension *dimension);
	/**@brief call this function last!
	 * @return the state space to be given to the constructor of MdpModel
	 * @sa MdpModel
	 */
	std::shared_ptr<StateSpace> getStateSpace();
private:
	void throwIfNoModel();
	void throwIfInconsistentNumberOfStates();
	std::vector<StateSpaceDimension *> dimensions;
	std::vector<PriorityState *> priorityStates;
	std::shared_ptr<DomainModel> domainModel;
	int nbOfStates{1};
	int nbOfPriorityStates{0};
	int nbOfDimensions{0};
};








}


#endif
