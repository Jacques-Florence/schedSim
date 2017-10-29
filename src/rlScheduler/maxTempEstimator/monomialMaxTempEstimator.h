/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MONOMIAL_MAX_TEMP_ESTIMATOR_H
#define MONOMIAL_MAX_TEMP_ESTIMATOR_H

#include "maxTempEstimator.h"

namespace Scheduler
{
	class Processor;
}

namespace RlScheduler
{

class MonomialMaxTempEstimator : public MaxTempEstimator
{
public:
	static constexpr const char *configKey = "monomialMaxTempEstimator";
public:
	MonomialMaxTempEstimator(int degree);
	double getMaximumTemperature() override;
private:
	const Scheduler::Processor * const proc{nullptr};
	int degree{2};
};

}

#endif
