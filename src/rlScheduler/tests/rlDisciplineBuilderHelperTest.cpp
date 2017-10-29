/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <rlScheduler/rlDisciplineBuilderHelper.h>
#include <mdp/builder.h>
#include <scheduler/schedulerConfiguration.h>
#include <rlScheduler/configuration.h>
#include <rlScheduler/domainModel.h>

#include <utils/randomGenerator.h>
#include <scheduler/process.h>
#include <scheduler/system.h>


TEST(HelperTest, testLcm)
{
	std::vector<std::shared_ptr<Scheduler::Process>> vect(3);
	vect[0] = Scheduler::Process::createRealTimeTask(0.0, 3.0, 0.0, 0);
	vect[1] = Scheduler::Process::createRealTimeTask(0.0, 4.0, 0.0, 0);
	vect[2] = Scheduler::Process::createRealTimeTask(0.0, 5.0, 0.0, 0);
	double result = RlScheduler::RlDisciplineBuilderHelper::lcm(vect);
	EXPECT_DOUBLE_EQ(3.0*4.0*5.0, result);

}

/*
class TestConfiguration : public RlScheduler::Configuration
{
public:
	TestConfiguration(std::string str) : RlScheduler::Configuration(str){};
	bool getBoolValue(std::string section, std::string key, bool def)
	{
		if (!section.compare("timeState"))
			return true;
		return Configuration::getBoolValue(section, key, def);
	};
};

TEST(HelperTest, testAddTimeStates)
{
	std::string name = "configuration.conf";
	Scheduler::SchedulerConfiguration schedConfig(name);
	Scheduler::System::buildSystem(&schedConfig);
	TestConfiguration config(name);
	Mdp::Builder builder(std::make_shared<RlScheduler::DomainModel>(&config));
	RlScheduler::RlDisciplineBuilderHelper::addTimeStates(&builder, &config);
}
*/



