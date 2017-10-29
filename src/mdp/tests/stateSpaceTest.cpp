/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "stateSpaceTest.h"
#include <iostream>
class StateSpaceTest : public ::testing::Test
{
public:
	std::shared_ptr<Mdp::StateSpace> stateSpace{nullptr};
	/*some stuff cannot be done in SetUp()*/
	void generateStateSpace();
	void SetUp() override;
	void TearDown() override;
};

void StateSpaceTest::SetUp()
{
	dim1 = new Dimension;
	dim2 = new Dimension;
	dim3 = new Dimension;
	prio1 = new Prio;
	prio2 = new Prio;
	std::cout << "DONE\n";
	std::cerr << "Done";
}

void StateSpaceTest::TearDown()
{
	/*dimensions are freed elsewere*/
}


void StateSpaceTest::generateStateSpace()
{
	Mdp::StateSpaceBuilder builder;
	builder.setDomainModel(std::make_shared<TestDomainModel>());
	builder.addPriorityState(prio1);
	builder.addPriorityState(prio2);
	builder.addDimension(dim1);
	builder.addDimension(dim2);
	builder.addDimension(dim3);
	stateSpace = builder.getStateSpace();
}



TEST_F(StateSpaceTest, testSize)
{
	dim1->nbOfPositions = 3;
	dim2->nbOfPositions = 7;
	dim3->nbOfPositions = 1;
	generateStateSpace();
	/* 23 = 3*7*1 + 2 priority states*/
	EXPECT_EQ(23u, stateSpace->size());
}


TEST_F(StateSpaceTest, testCurrentState)
{
	dim1->nbOfPositions = 3;
	dim1->position = 0;
	dim2->nbOfPositions = 7;
	dim2->position = 0;
	dim3->nbOfPositions = 1;
	generateStateSpace();
	stateSpace->updateCurrentState();
	EXPECT_EQ((Mdp::state_t) 0, stateSpace->getState());	

	dim1->nbOfPositions = 3;
	dim1->position = 2;
	dim2->nbOfPositions = 7;
	dim2->position = 4;
	dim3->nbOfPositions = 1;
	stateSpace->updateCurrentState();
	/* 2*1 + 4*(3) + 0*(3*7) = 14 */
	EXPECT_EQ((Mdp::state_t) 14, stateSpace->getState());	

	dim1->nbOfPositions = 3;
	dim1->position = 0;
	dim2->nbOfPositions = 7;
	dim2->position = 5;
	dim3->nbOfPositions = 3;
	dim3->position = 1;
	stateSpace->updateCurrentState();
	/* 0*1 + 5*(3) + 1*(3*7)= 19 */
	EXPECT_EQ((Mdp::state_t) 36, stateSpace->getState());	
}


TEST_F(StateSpaceTest, testCurrentPriorityState)
{
	dim1->nbOfPositions = 3;
	dim1->position = 0;
	dim2->nbOfPositions = 7;
	dim2->position = 5;
	dim3->nbOfPositions = 3;
	dim3->position = 1;
	prio1->inState = true;
	generateStateSpace();
	stateSpace->updateCurrentState();
	EXPECT_EQ((Mdp::state_t) 63, stateSpace->getState());	

	prio1->inState = false;
	prio2->inState = true;
	stateSpace->updateCurrentState();
	EXPECT_EQ((Mdp::state_t) 64, stateSpace->getState());	

	prio1->inState = true;
	prio1->inState = true;
	stateSpace->updateCurrentState();
	/*The first priority state added has priority over other priority states*/
	EXPECT_EQ((Mdp::state_t) 63, stateSpace->getState());	
}


TEST_F(StateSpaceTest, testGetReward)
{
	generateStateSpace();
	double reward = stateSpace->getReward();
	EXPECT_DOUBLE_EQ(expectedReward, reward);
}








