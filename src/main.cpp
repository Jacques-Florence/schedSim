/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <cassert>
#include <iostream>
#include <vector>

#include <utils/configuration.h>
#include <utils/programTime.h>

#include <scheduler/schedulingSimulator.h>
#include <scheduler/system.h>
#include <scheduler/process.h>
#include <scheduler/taskSetGenerator.h>

#include <rlScheduler/configuration.h>

int main(int argc, char *argv[])
{
#ifdef PRINT
	std::cerr << "Hello!\n";
#endif
	Utils::ProgramTime::init();
	
	std::string defaultConfigName = "configuration/configuration.conf";
	std::string configName;
#ifdef PRINT
	std::cout << "argc is "<< argc <<"\n";
	std::cout << "The arguments are:\n";
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << "\n";
#endif
	configName = (argc == 2 ? argv[1]: defaultConfigName);

	
	std::shared_ptr<RlScheduler::Configuration> conf = std::make_shared<RlScheduler::Configuration>(configName);
	assert(conf != nullptr);
	Scheduler::SchedulingSimulator simulator(conf);

	simulator.seedRandomGenerator(123);
	
	simulator.initializeTaskSet();

	simulator.turnOnProcessor(0.0);
	//simulator.setDummyEvent(0.0, 1.0);

	//simulator.setStatsTick(1.0, 10);
	//simulator.setUsageCalculationTimeout(1.0, 100.0);
	//simulator.setFreqUpdate(1.0, 100.0);
	//simulator.setSchedulerTimeout(1.0, 2.0);
	Scheduler::System::getInstance()->printProcessesReport();

	simulator.endSimulation(conf->getRunningTime());

	simulator.startScheduler();
#ifdef PRINT
	std::cerr << "time spent: "<< Utils::ProgramTime::elapsedTimeInSeconds() <<"\n";
#endif
	return 0;

}











