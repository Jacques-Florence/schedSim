#include <iostream>

#include <scheduler/schedulingSimulator.h>
#include <scheduler/schedulerConfiguration.h>

int main()
{	
	Scheduler::SchedulingSimulator simulator;
	simulator.seedRandomGenerator(123);
	
	simulator.createRealTimeTask(0.0, 15.0, 15.0, 7.0);
	simulator.createInteractiveProcess(1.0);

	simulator.turnOnProcessor(0.0);
	simulator.setSchedulerTimeout(1.0, 2.0);
	simulator.endSimulation(50);

	simulator.startScheduler();
	return 0;
}
