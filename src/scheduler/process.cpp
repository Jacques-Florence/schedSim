/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "process.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <thread>

#include <utils/randomGenerator.h>
#include <utils/distributions/boundedRandomDistribution.h>

#include "time.h"


using namespace Scheduler;

unsigned long int Process::currentNumber = 0;
Utils::RandomGenerator *Process::randomGenerator = nullptr;


std::shared_ptr<Process> Process::createNextJob(const Process& task)
{
	assert(task.RT);
	std::vector<double> burst(1);
	std::shared_ptr<Process> job = std::make_shared<Process>(task.pid, 1, burst, std::vector<double>(), task.priority);

	/*TODO: put this in function setRealTimeParams*/
	job->RT = true;
	job->deadline = task.deadline;
	job->deadlineTime = task.deadlineTime;
	job->period = task.period;
	job->bcet = task.bcet;
	job->wcet = task.wcet;
	job->powerCoeff = task.powerCoeff;
	job->jobNumber = task.jobNumber + 1;
	job->randomDist = task.randomDist;
	job->setDuration();
	return job;
}


std::shared_ptr<Process> Process::createProcess(double cpuLambda, double ioLambda)
{
	assert(randomGenerator != nullptr);
	int nbBursts = 10;
	std::vector<double> cpuBurst = std::vector<double>(nbBursts);
	std::vector<double> ioBurst = std::vector<double>(nbBursts);
	for (int i = 0; i < nbBursts; i++)
	{
		cpuBurst[i] = randomGenerator->drawExp(cpuLambda)*100;//TODO: why *100 here but not next line?
		ioBurst[i] = randomGenerator->drawExp(ioLambda);
	}
	std::shared_ptr<Process> p = std::make_shared<Process>(Process::getNewPid(), nbBursts, cpuBurst, ioBurst);
	return p;
}

std::shared_ptr<Process> Process::createRealTimeTask(
	  double wcet
	, double T
	, double dl
	, int pid
	, int priority
	, double bcet
	)
{
	int nbBursts = 1;
	std::vector<double> cpuBurst = std::vector<double>(nbBursts);
	std::vector<double> ioBurst = std::vector<double>(nbBursts);
	std::cerr << "in Process, wcet is " << wcet <<"\n";
	cpuBurst[0] = wcet;
	ioBurst[0] = 0;
	std::shared_ptr<Process> p = std::make_shared<Process>(pid, nbBursts, cpuBurst, ioBurst, priority);
	p->setRtParams(dl, T, wcet, bcet);
	return p;
}


int Process::getNewPid()
{
	static int pid = 0;
	return pid++;
}

unsigned long int Process::getMaxNumber()
{
	return maxNumber;
}

void Process::setRandomGenerator(Utils::RandomGenerator *gen)
{
	randomGenerator = gen;
}
void Process::end()
{
}




Process::Process(int p, int nb, std::vector<double> cpu, std::vector<double> io, int pri)
	: pid(p)
	, cpuBurst(cpu)
	, ioBurst(io)
	, currentBurst(0)
	, nbBursts(nb)
	, priority(pri)
{
	if(currentNumber++ > maxNumber)
		throw std::runtime_error("too many processes created");
}

Process::Process(const Process& task)
{
	if(currentNumber++ > maxNumber)
		throw "too many processes created";
	currentBurst = 0;
	pid = task.pid;
	powerCoeff = task.powerCoeff;
	nbBursts = task.nbBursts;
	cpuBurst = std::vector<double>(nbBursts);
	ioBurst = std::vector<double>(nbBursts);
	for (int i = 0; i < nbBursts; i++)
	{
		cpuBurst[i] = task.cpuBurst[i];
		ioBurst[i] = task.ioBurst[i];
	}
	priority = task.priority;
	RT = task.RT;
	deadline = task.deadline;
	deadlineTime = 0.0; //this will have to be modified anyway?
	period = task.period;
	bcet = task.bcet;
	wcet = task.wcet;
	jobNumber = task.jobNumber;
	randomDist = task.randomDist;
}

Process::~Process()
{
}


void Process::setDurationDistribution(std::shared_ptr<Utils::BoundedRandomDistribution> rd)
{
	randomDist = rd;
}

int Process::getPid() const
{
	return pid;
}

int Process::getPriority() const
{
	return priority;
}

void Process::setPriority(int pri)
{
	priority = pri;
}

bool Process::advanceBurst()
{
	currentBurst++;
	return currentBurst < nbBursts;
}

void Process::decrementBurst()
{
	currentBurst--;
}

double Process::getCurrentCpuAow() const
{
	return cpuBurst[currentBurst];
}

double Process::getCurrentIoTime() const
{
	if (nbBursts > currentBurst && ioBurst.size() > 0)
		return ioBurst[currentBurst];
	else
		return -1;
}

double Process::getWcet() const
{
	return wcet;
}


void Process::setDuration()
{
	assert(nbBursts == 1);
	assert(bcet <= wcet);
	double duration = (randomDist == nullptr ? 1.0 : randomDist->draw());
	duration = bcet + (wcet-bcet)*duration;
	cpuBurst[0] = duration;
}


void Process::setRtParams(double dl, double T, double w, double b)
{
	deadline = dl;
	period = T;
	RT = true;
	wcet = w;
	bcet = b;
}

void Process::setDeadlineTimeFromStartTime(double startTime)
{
	deadlineTime = deadline + startTime;
}

double Process::getDeadline() const
{
	return deadline;
}


bool Process::isRealTime() const
{
	return RT;
}




void Process::updateCurrentAow(double aow)
{
	cpuBurst[--currentBurst] = aow;
}

double Process::getPeriod() const
{
	return period;
}

double Process::getDeadlineTime() const
{
	return deadlineTime;
}

void Process::print(std::ostream& stream) const
{
	stream << "Processs "<<pid<<":\n";
	stream << "    priority: "<<priority<<"\n";
	stream << "    Bursts:\n";
	for (int i = 0; i < nbBursts; i++)
	{
		stream << "      "<< i <<". CPU: "<< cpuBurst[i] <<"\n";
		stream << "                        IO: " << ioBurst[i] <<"\n";
	}
	stream << "    Power coefficient: "<< powerCoeff<<"\n";
	if (RT)
	{
		stream << "    This proces IS real-time\n";
		stream << "    Deadline: "<< deadline <<"\n";
		//stream << "    Absolute deadline: "<< deadlineTime <<"\n";
		stream << "    Period: "<< period <<"\n";
	}
	else
	{
		stream << "    This process IS NOT real-time\n";
	}
	stream << "\n";
}


void Process::incrementJobNumber()
{
	jobNumber++;
}

unsigned int Process::getJobNumber() const
{
	return jobNumber;
}


void Process::setPowerCoeff(double coeff)
{
	powerCoeff = coeff;
}




