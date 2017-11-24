#include <iostream>

#include <scheduler/freqConstants.h>
#include <scheduler/schedulingSimulator.h>
#include <scheduler/schedulerConfiguration.h>

int main()
{	
	Scheduler::SchedulingSimulator simulator;
	simulator.seedRandomGenerator(123);
	
	simulator.createRealTimeTask(0.0, 15.0, 15.0*MINFREQ,  7.0);
	simulator.createRealTimeTask(0.0, 20.0, 15.0*MINFREQ, 20.0);

	simulator.turnOnProcessor(0.0);
	simulator.endSimulation(600);

	simulator.startScheduler();
	return 0;
}
