/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef DOMAINMODEL_H
#define DOMAINMODEL_H


namespace Mdp
{


class DomainModel
{
public:
	virtual ~DomainModel(){};
	/*The rewards can be provided to the mdp frameword via two means:
	 *-Either we provide a full table of (state-action;rewards),
	 *-Or we let the learning strategy learn this table by measuring
	 *	the reward obtained from the environment via the measureReward method.*/
	virtual double measureReward()=0;

};






}


#endif
