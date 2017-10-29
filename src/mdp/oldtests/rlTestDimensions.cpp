/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "rlTestDimensions.h"


RlDim::RlDim(int i) : nbPos(i)
{
}


int RlDim::getNumberOfPositions()
{
	return nbPos;
}


Mdp::statePosition_t RlDim::getPosition()
{
	return (nbPos == 12) ? getModel<RlTestDomainModel>()->xpos: getModel<RlTestDomainModel>()->ypos;
}





