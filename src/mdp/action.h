/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

namespace Mdp
{

class ActionSpace;
class ActionSpaceBuilder;
class DomainModel;

class Action
{
friend ActionSpace;
friend ActionSpaceBuilder;
public:
	virtual ~Action(){};
	virtual std::string getName()=0;
	virtual void performAction()=0;
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


class DummyAction : public Action
{
	std::string getName(){return "DummyAction";};
	void performAction(){std::cout << "Dummy action performed\n";};
};



}



#endif
