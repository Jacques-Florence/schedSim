/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <utils/math.h>
#include <gtest/gtest.h>




TEST(mathTest, lcm)
{
	EXPECT_EQ(0, Utils::lcm(std::vector<int>(1, 0)));
	EXPECT_EQ(1, Utils::lcm(std::vector<int>(1, 1)));
	std::vector<int> vect1{2, 2};
	EXPECT_EQ(2, Utils::lcm(vect1));
	std::vector<int> vect2{2, 3};
	EXPECT_EQ(6, Utils::lcm(vect2));
	std::vector<int> vect3{2, 3, 4, 5, 7};
	EXPECT_EQ(420, Utils::lcm(vect3));
}










