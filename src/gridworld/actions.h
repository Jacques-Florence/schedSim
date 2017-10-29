/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <mdp/action.h>


namespace Gridworld
{

class Up : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() verride;
};

class Down : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() verride;
};

class Left : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() verride;
};

class Right : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() verride;
};


}

