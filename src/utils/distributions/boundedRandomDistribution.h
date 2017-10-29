/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef BOUNDED_RANDOM_DISTRIBUTION_H
#define BOUNDED_RANDOM_DISTRIBUTION_H

namespace Utils
{

/**
 */
class BoundedRandomDistribution
{
public:
	virtual ~BoundedRandomDistribution(){};
	/**@brief returns a number from 0 to 1 following the underlying probability distribution
	 */
	virtual double draw()=0;
};

}


#endif
