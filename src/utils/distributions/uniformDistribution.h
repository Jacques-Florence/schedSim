/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef UNIFORM_DISTRIBUTION_H
#define UNIFORM_DISTRIBUTION_H

#include "boundedRandomDistribution.h"

namespace Utils
{

class RandomGenerator;


class UniformDistribution : public BoundedRandomDistribution
{
public:
	UniformDistribution(RandomGenerator *gen);
	double draw() override;
private:
	RandomGenerator *gen{nullptr};
};

}

#endif
