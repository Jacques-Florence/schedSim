/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RLTESTDOMAINMODEL_H
#define RLTESTDOMAINMODEL_H

#include <mdp/domainModel.h>


class RlTestDomainModel : public Mdp::DomainModel
{
public:
	int xpos{0};
	int ypos{0};
	double measureReward();



};
#endif
