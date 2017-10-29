/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <scheduler/process.h>
#include <utils/randomGenerator.h>

using namespace Scheduler;

TEST(ProcessTest, createProcess)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	auto process = Process::createProcess(1.0, 1.0);
	ASSERT_NE(process, nullptr);
	EXPECT_FALSE(process->isRealTime());

}

TEST(ProcessTest, priority)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	auto process = Process::createProcess(1.0,1.0);
	process->setPriority(5);
	EXPECT_EQ(process->getPriority(), 5);
}

TEST(ProcessTest, createRealTimeTask)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	double wcet = 10.0;
	double period = 30.0;
	double deadline = 28;
	int pid = 4;
	int priority = 1;
	double bcet = wcet;
	auto process = Process::createRealTimeTask(wcet, period, deadline, pid, priority, bcet);
	ASSERT_NE(process, nullptr);
	EXPECT_TRUE(process->isRealTime());
	EXPECT_EQ(process->getPid(), pid);
	EXPECT_DOUBLE_EQ(process->getPeriod(), period);
	EXPECT_DOUBLE_EQ(process->getDeadline(), deadline);
	EXPECT_EQ(process->getJobNumber(), (unsigned)0);
	EXPECT_DOUBLE_EQ(process->getWcet(), wcet);
	process->incrementJobNumber();
	EXPECT_EQ(process->getJobNumber(), (unsigned)1);
}

TEST(ProcessTest, createNextJob)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	double wcet = 10.0;
	double period = 30.0;
	double deadline = 28;
	int pid = 4;
	int priority = 1;
	double bcet = wcet;
	auto process1 = Process::createRealTimeTask(wcet, period, deadline, pid, priority, bcet);
	auto process2 = Process::createNextJob(*process1);
	ASSERT_NE(process2, nullptr);
	EXPECT_TRUE(process2->isRealTime());
	EXPECT_EQ(process2->getPid(), pid);
	EXPECT_DOUBLE_EQ(process2->getPeriod(), period);
	EXPECT_DOUBLE_EQ(process2->getDeadline(), deadline);
	EXPECT_DOUBLE_EQ(process2->getWcet(), wcet);
	EXPECT_EQ(process2->getJobNumber(), (unsigned)1);
}

TEST(ProcessTest, getNewPid)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	auto pid1 = Process::getNewPid();
	auto pid2 = Process::getNewPid();
	EXPECT_EQ(pid2, pid1+1);
}

TEST(ProcessTest, DISABLED_randomGenerator)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	double wcet = 10.0;
	double period = 30.0;
	double deadline = 28;
	int pid = 4;
	int priority = 1;
	double bcet = wcet;
	auto process = Process::createRealTimeTask(wcet, period, deadline, pid, priority, bcet);
	ASSERT_NE(process, nullptr);
}

TEST(ProcessTest, manageAow)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	double wcet = 10.0;
	double period = 30.0;
	double deadline = 28;
	int pid = 4;
	int priority = 1;
	double bcet = wcet;
	auto process = Process::createRealTimeTask(wcet, period, deadline, pid, priority, bcet);
	ASSERT_NE(process, nullptr);
	EXPECT_DOUBLE_EQ(process->getCurrentCpuAow(), wcet);
	process->advanceBurst();//TODO poor design
	process->updateCurrentAow(8.5);
	EXPECT_DOUBLE_EQ(process->getCurrentCpuAow(), 8.5);
}

TEST(ProcessTest, deadlineTime)
{
	Process::setRandomGenerator(new Utils::RandomGenerator);
	double wcet = 10.0;
	double period = 30.0;
	double deadline = 28;
	int pid = 4;
	int priority = 1;
	double bcet = wcet;
	auto process = Process::createRealTimeTask(wcet, period, deadline, pid, priority, bcet);
	ASSERT_NE(process, nullptr);

	process->setDeadlineTimeFromStartTime(1.0);
	EXPECT_DOUBLE_EQ(process->getDeadline(), deadline);
	EXPECT_DOUBLE_EQ(process->getDeadlineTime(), deadline + 1.0);
}











