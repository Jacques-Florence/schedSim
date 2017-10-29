/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef SQUARE_MAX_TEMP_ESTIMATOR_H
#define SQUARE_MAX_TEMP_ESTIMATOR_H

#include "maxTempEstimator.h"

namespace Scheduler
{
	class Processor;
}

namespace RlScheduler
{

class SquareMaxTempEstimator : public MaxTempEstimator
{
public:
	static constexpr const char *configKey = "squareTempEstimator";
public:
	SquareMaxTempEstimator();
	double getMaximumTemperature() override;
private:
	const Scheduler::Processor * const proc{nullptr};
};

}

#endif
