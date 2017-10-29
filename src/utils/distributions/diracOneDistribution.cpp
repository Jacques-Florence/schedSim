/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "diracOneDistribution.h"

using namespace Utils;

DiracOneDistribution::DiracOneDistribution(RandomGenerator *)
{
}

double DiracOneDistribution::draw()
{
	return 1.0;
}
