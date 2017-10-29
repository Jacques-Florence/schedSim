/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "stateSpaceTest.h"

class StateSpaceBuilderTest : public ::testing::Test
{
public:
	std::shared_ptr<Mdp::StateSpace> stateSpace{nullptr};
	Mdp::StateSpaceBuilder builder;
	void SetUp() override;
	void TearDown() override;
};

void StateSpaceBuilderTest::SetUp()
{
	dim1 = new Dimension;
	dim2 = new Dimension;
	dim3 = new Dimension;
	prio1 = new Prio;
	prio2 = new Prio;
}

void StateSpaceBuilderTest::TearDown()
{
	/*nothing to do*/
}

void setDomainModel(Mdp::StateSpaceBuilder *builder)
{
	builder->setDomainModel(std::make_shared<TestDomainModel>());
}

TEST_F(StateSpaceBuilderTest, throwsIfNoStateAndNoDimension)
{
	setDomainModel(&builder);
	EXPECT_THROW(builder.getStateSpace(), std::runtime_error);
}

void addOneDimensionAndBuild(Mdp::StateSpaceDimension *dim, Mdp::StateSpaceBuilder *builder)
{
	builder->addDimension(dim);
	builder->getStateSpace();
}

TEST_F(StateSpaceBuilderTest, throwsIfDimensionHasZeroPositions)
{
	setDomainModel(&builder);
	dim1->nbOfPositions = 0;
	EXPECT_THROW(addOneDimensionAndBuild(dim1, &builder), std::runtime_error);
}

TEST_F(StateSpaceBuilderTest, throwsIfDomainModelNotSet)
{
	dim1->nbOfPositions = 2;
	EXPECT_THROW(addOneDimensionAndBuild(dim1, &builder), std::runtime_error);
}

TEST_F(StateSpaceBuilderTest, stateSpaceHasRightNumberOfStates)
{
	dim1->nbOfPositions = 2;
	dim2->nbOfPositions = 3;
	setDomainModel(&builder);
	builder.addDimension(dim1);
	builder.addDimension(dim2);
	builder.addPriorityState(prio1);
	builder.addPriorityState(prio2);
	stateSpace = builder.getStateSpace();
	EXPECT_EQ(dim1->nbOfPositions * dim2->nbOfPositions + 2u, stateSpace->size());
	EXPECT_EQ(8u, stateSpace->size());
}








