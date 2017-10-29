/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef BERNOULLI_H
#define BERNOULLI_H

#include "boundedRandomDistribution.h"

namespace Utils
{

class RandomGenerator;

class Bernoulli : public BoundedRandomDistribution
{
public:
	/**
	 *This is a Bernoulli distribution.
	 *@param p is the probability of drawing a one*/
	Bernoulli(RandomGenerator *gen, double p);
	virtual ~Bernoulli(){};
	double draw() override;
private:
	RandomGenerator *gen{nullptr};
	double p{0.5};
};

}
#endif
