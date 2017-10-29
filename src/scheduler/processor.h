/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <memory>

#include <utils/record.h>
#include <utils/configuration.h>

#include "freqConstants.h"
#include "temperatureModel/temperatureModel.h"

namespace Scheduler
{

class Process;
class TemperatureModel;

class Processor
{
public:
	Processor(std::shared_ptr<Utils::Configuration>);
	~Processor();
	/**@brief get the current frequency of the processor
	 */
	double getFreq() const;
	/**@brief set the current frequency of the processor
	 */
	void setFreq(double);
	/**@brief get the minimum frequency at which this processor can operate
	 */
	double getMinFreq() const;
	/**@brief get the maximum frequency at which this processor can operate
	 */
	double getMaxFreq() const;
	/**@brief get the current usage of the processor
	 *
	 * @return the usage as a number between 0.0 (idle) and 1.0 (busy 100% of the time)
	 * The value returned is the value computed during the last call to updateUsage
	 */
	double getUsage() const;
	/**@brief updates the value of the usage percentage.
	 */
	void updateUsage();
	void reinitTicks();
	void updateTicks();
	/**@brief returns true if the processor is running the task provided as argument
	 */
	bool isRunning(std::shared_ptr<Process> p) const;
	void setRunning(std::shared_ptr<Process> p);
	std::shared_ptr<Process> getRunningTask();
	void setTemperatureModel(TemperatureModel *);
	TemperatureModel *getTemperatureModel();
	void updateTemperature(double timeInterval);
	double getTemperature() const;
	void printReports(std::string folder) const;
	void printTemperatureReport(std::string folder) const;
	void printEnergyReport(std::string folder) const;
	void printUsageReport(std::string folder) const;
	void printFreqReport(std::string folder) const;
	/**@brief return true if the processor is running any task
	 */
	bool isBusy() const;
	/**@brief power the processor on or off
	 * @param p if true, power on, otherwise, power off
	 */
	void power(bool p);
	/**@brief return true if the processor is powered on
	 */
	bool powered() const;
private:
	std::shared_ptr<Utils::Configuration> conf;
	const double maxFreq{MAXFREQ}; /*frequency in MHz*/
	const double minFreq{MINFREQ};
	double usage{0.0};
	double freq{0.0};
	std::shared_ptr<Process> runningTask{nullptr};
	long long int totalBusyTicks{0};
	long long int totalIdleTicks{0};
	long long int previousIdleTicks{0};
	long long int previousBusyTicks{0}; 
	Utils::Record usageHistory;
	Utils::Record freqHistory;
	struct PowerParams powerParams;
	TemperatureModel *temperatureModel{nullptr};

	bool busy{false};
};

}

#endif
