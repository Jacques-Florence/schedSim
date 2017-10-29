/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RLTESTDIMENSIONS_H
#define RLTESTDIMENSIONS_H

#include <mdp/stateSpaceDimension.h>

#include <stdexcept>
#include <memory>

#include "rlTestDomainModel.h"

typedef std::shared_ptr<RlTestDomainModel> RlModelPtr;


class RlDim : public Mdp::StateSpaceDimension
{
public:
	RlDim(int i);
	std::string getName(){return "dim";};
	Mdp::statePosition_t getPosition();
	int getNumberOfPositions();
private:
	size_t nbPos;
};

#endif
