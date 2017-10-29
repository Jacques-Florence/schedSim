/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef HORIZON_H
#define HORIZON_H


namespace Mdp
{

struct Horizon
{
	bool finiteHorizon;
	double discountFactor;
	std::vector<double> initialStateDistribution;
};

}

#endif
