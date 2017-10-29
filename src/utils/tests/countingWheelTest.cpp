/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <utils/countingWheel.h>


TEST(CountingWheel, testInitialization)
{
	Utils::CountingWheel wheel(7);
	wheel.initialize();
	EXPECT_EQ(0u, wheel.getValue());
	EXPECT_EQ(7u, wheel.getBase());
}


TEST(CountingWheel, incrementAndCarryTest)
{
	Utils::CountingWheel wheel(3);
	wheel.initialize();
	bool carry = wheel.increment();
	EXPECT_EQ(1u, wheel.getValue());
	EXPECT_FALSE(carry);

	carry = wheel.increment();
	EXPECT_EQ(2u, wheel.getValue());
	EXPECT_FALSE(carry);

	carry = wheel.increment();
	EXPECT_EQ(0u, wheel.getValue());
	EXPECT_TRUE(carry);
}
TEST(CountingWheel, baseZeroTest)
{
	Utils::CountingWheel wheel0(0);
	bool carry = false;
	wheel0.initialize();
	EXPECT_EQ(0u, wheel0.getValue());
	carry = wheel0.increment();
	EXPECT_EQ(0u, wheel0.getValue());
	EXPECT_TRUE(carry);
}


