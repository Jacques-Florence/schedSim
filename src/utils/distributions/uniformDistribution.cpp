/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "uniformDistribution.h"

#include <utils/randomGenerator.h>

using namespace Utils;


UniformDistribution::UniformDistribution(RandomGenerator *g) : gen(g)
{
}

double UniformDistribution::draw()
{
	return gen->drawUniform(0.0, 1.0);
}



