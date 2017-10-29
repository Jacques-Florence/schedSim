/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPSTATESPACEDIMENSION_H
#define MDPSTATESPACEDIMENSION_H

#include <memory>
#include <string>
#include <stdexcept>

namespace Mdp
{
typedef int statePosition_t; //TODO: make this unsigned

class DomainModel;
class StateSpaceBuilder;
class StateSpace;

/**@brief this models a dimension in the state space.

 * This abstract class has to be implemented into actual dimensions by the client of the MDP framework
 */
class StateSpaceDimension
{
friend StateSpace; /*TODO: is this line necessary?*/
friend StateSpaceBuilder;
public:
	virtual ~StateSpaceDimension(){};
	/**@brief returns the name of that dimension
	 */
	virtual std::string getName()=0;
	/**@brief gets the position of the state along that dimension
	 * @return a position starting at 0 along that dimension of the (discrete finite) space. 
	 */
	virtual statePosition_t getPosition()=0;
	/**@brief returns the number of possible positions along that dimension
	 */
	virtual size_t getNumberOfPositions()=0;
	void setIndex(int i);
	int getIndex();
protected:
	template<typename T>
	std::shared_ptr<T> getModel()
	{
		std::shared_ptr<T> model = std::dynamic_pointer_cast<T>(domainModel);
		if (model == nullptr)
			throw std::runtime_error("inconsistent domain model type");
		return model;
	}
	int index;
	std::shared_ptr<DomainModel> domainModel{nullptr};
};






class TestOnlyDimension : public StateSpaceDimension
{
public:
	static constexpr const char *configKey = "FOR TEST PURPOSE ONLY";
public:
	~TestOnlyDimension(){};
	std::string getName(){return TestOnlyDimension::configKey;};
	statePosition_t getPosition(){return -1;};
	size_t getNumberOfPositions(){return nbPos;};
	void setNumberOfPositions(int n){nbPos = n;};
private:
	size_t nbPos{1};
};




}
#endif
