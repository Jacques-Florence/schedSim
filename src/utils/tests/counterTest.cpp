/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <utils/counter.h>


TEST(CounterTest, initializationAndIncrementTest)
{
	Utils::Counter counter;
	counter.addWheel(2);
	counter.addWheel(3);

	counter.initialize();
	std::vector<unsigned int> value = counter.getValue();
	EXPECT_EQ(0u, value[0]);
	EXPECT_EQ(0u, value[1]);

	counter.increment();
	value = counter.getValue();
	EXPECT_EQ(1u, value[0]);
	EXPECT_EQ(0u, value[1]);

	counter.increment();
	value = counter.getValue();
	EXPECT_EQ(0u, value[0]);
	EXPECT_EQ(1u, value[1]);

	counter.increment();
	counter.increment();
	counter.increment();
	
	counter.increment();
	value = counter.getValue();
	EXPECT_EQ(0u, value[0]);
	EXPECT_EQ(0u, value[1]);
}

TEST(CounterTest, numberOfValuesTest)
{
	
	Utils::Counter counter;
	counter.addWheel(2);
	counter.addWheel(3);
	EXPECT_EQ(6u, counter.getNumberOfValues());
}




















