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

#include <scheduler/freqConstants.h>
#include <scheduler/schedulingSimulator.h>
#include <scheduler/schedulerConfiguration.h>
#include <scheduler/system.h>
#include <scheduler/process.h>
#include <scheduler/taskSetGenerator.h>


int main(int argc, char *argv[])
{
	Utils::ProgramTime::init();
	
	std::string defaultConfigName = "configuration/configuration.conf";
	std::string configName;
	configName = (argc == 2 ? argv[1]: defaultConfigName);

	
	std::shared_ptr<Scheduler::SchedulerConfiguration> conf = std::make_shared<Scheduler::SchedulerConfiguration>(configName);
	assert(conf != nullptr);
	Scheduler::SchedulingSimulator simulator(conf);

	simulator.seedRandomGenerator(123);
	
	simulator.createRealTimeTask(0.0, 15.0, 5.0*MINFREQ, 15.0);
	simulator.createRealTimeTask(0.0, 20.0, 6.0*MINFREQ, 20.0);

	simulator.turnOnProcessor(-0.0001);
	Scheduler::System::getInstance()->printProcessesReport();

	simulator.endSimulation(conf->getRunningTime());

	simulator.startScheduler();
	return 0;

}











