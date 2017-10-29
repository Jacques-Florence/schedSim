/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "bernoulli.h"
#include <utils/randomGenerator.h>
#include <stdexcept>


using namespace Utils;


Bernoulli::Bernoulli(RandomGenerator *generator, double success_p)
	: gen(generator)
	, p(success_p)
{
	if (p < 0.0 || p > 1.0)
		throw std::domain_error("p should be between 0 and 1");
}



double Bernoulli::draw()
{
	double random = gen->drawUniform(0.0, 1.0);
	if (random < p)
		return 1.0;
	return 0.0;
}

