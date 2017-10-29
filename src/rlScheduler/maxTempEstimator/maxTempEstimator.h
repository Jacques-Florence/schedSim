/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MAX_TEMP_ESTIMATOR_H
#define MAX_TEMP_ESTIMATOR_H

namespace RlScheduler
{

class MaxTempEstimator
{
public:
	virtual ~MaxTempEstimator(){};
	virtual double getMaximumTemperature()=0;
};

}

#endif
