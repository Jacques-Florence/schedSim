/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef EXPONENTIAL_MAX_TEMP_ESTIMATOR_H
#define EXPONENTIAL_MAX_TEMP_ESTIMATOR_H


#include "maxTempEstimator.h"

namespace Scheduler
{
	class Processor;
}

namespace RlScheduler
{

class ExponentialMaxTempEstimator : public MaxTempEstimator
{
public:
	static constexpr const char *configKey = "exponentialTempEstimator";
public:
	ExponentialMaxTempEstimator(double scaling, double offset);
	double getMaximumTemperature() override;
private:
	Scheduler::Processor *proc{nullptr};
	double scaling{1.0};
	double offset{0.0};
};

}
#endif
