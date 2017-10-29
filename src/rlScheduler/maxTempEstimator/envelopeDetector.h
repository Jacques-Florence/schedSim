/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef ENVELOPE_DETECTOR_H
#define ENVELOPE_DETECTOR_H

#include "maxTempEstimator.h"

namespace Scheduler
{
	class Processor;
}

namespace RlScheduler
{

class EnvelopeDetector : public MaxTempEstimator
{
public:
	static const constexpr char *configKey = "envelopeDetector";
public:
	EnvelopeDetector(double decayCoeff);
	double getMaximumTemperature() override;
private:
	double decayCoeff{0.999};
	double maxTemp{-300.0}; //-300 degrees Celcius is below absolute zero
	Scheduler::Processor *proc;
};


}
#endif

