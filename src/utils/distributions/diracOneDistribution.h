/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef DIRAC_ONE_DISTRIBUTION_H
#define DIRAC_ONE_DISTRIBUTION_H

#include "boundedRandomDistribution.h"

namespace Utils
{

class RandomGenerator;

class DiracOneDistribution : public BoundedRandomDistribution
{
public:
	DiracOneDistribution(RandomGenerator *);
	double draw() override;
};

}
#endif

