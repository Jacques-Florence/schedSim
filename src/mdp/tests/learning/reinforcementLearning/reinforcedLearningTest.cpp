/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <mdp/learning/reinforcementLearning/reinforcedLearning.h>
#include <gtest/gtest.h>

#include <mdp/context.h>
#include <mdp/policy.h>
#include <mdp/stateSpace.h>
#include <mdp/mdpConfiguration.h>
#include <utils/randomGenerator.h>

using namespace Mdp;

class RlTester : public ReinforcedLearning
{
public:
	RlTester(std::shared_ptr<Context> context) : ReinforcedLearning(context){};
};

size_t NBOFSTATES = 5;
size_t NBOFACTIONS = 4;

class CustomStateSpace : public StateSpace
{
public:
	CustomStateSpace() : StateSpace(){};
	size_t size() override {return NBOFSTATES;};
	state_t getState() override {return 0;};
	void updateCurrentState() override {};
	double getReward() override {return 1.0;};
};

class CustomActionSpace : public ActionSpace
{
public:
	size_t size() override {return NBOFACTIONS;};
};

std::shared_ptr<Context> buildContext()
{
	std::shared_ptr<Context> context = std::make_shared<Context>();
	std::shared_ptr<Utils::RandomGenerator> gen = std::make_shared<Utils::RandomGenerator>();
	std::shared_ptr<Policy> policy = std::make_shared<Policy>(NBOFSTATES, NBOFACTIONS, context->randomGenerator);
	
	std::shared_ptr<CustomStateSpace> stateSpace = std::make_shared<CustomStateSpace>();
	std::shared_ptr<CustomActionSpace> actionSpace = std::make_shared<CustomActionSpace>();
	std::shared_ptr<MdpConfiguration> conf = std::make_shared<MdpConfiguration>("configuration.conf");
	
	context->randomGenerator = gen;
	context->policy = policy;
	context->stateSpace = stateSpace;
	context->actionSpace = actionSpace;
	context->conf = conf;
	return context;
}

TEST(ReinforcementLearningTest, testBasic)
{
	std::shared_ptr<Context> context = buildContext();
	RlTester tester(context);
	tester.initializeModel();
	tester.end();
}





