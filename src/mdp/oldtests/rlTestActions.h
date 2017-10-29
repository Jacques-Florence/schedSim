/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RLTESTACTIONS_H
#define RLTESTACTIONS_H

#include <memory>

#include <mdp/action.h>

#include "rlTestDimensions.h" //for the typedef


class GoUp : public Mdp::Action
{
public:
	std::string getName() override;
	void performAction() override;
};

class GoDown : public Mdp::Action
{

public:
	std::string getName() override;
	void performAction() override;
};

class GoLeft : public Mdp::Action
{

public:
	std::string getName() override;
	void performAction() override;
};


class GoRight : public Mdp::Action
{

public:
	std::string getName() override;
	void performAction() override;
};


#endif
