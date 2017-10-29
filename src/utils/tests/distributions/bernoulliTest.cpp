/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <utils/distributions/bernoulli.h>
#include <utils/randomGenerator.h>
#include <stdexcept>

#define NB_ITER 10000

int drawSeveralTimes(int times, double p)
{

	Utils::RandomGenerator *gen;
	gen = new Utils::RandomGenerator;
	Utils::Bernoulli bern(gen, p);
	int successCount = 0;
	for (int i = 0; i < times; i++)
	{
		double result = bern.draw();
		if (result > 0.5)
			successCount++;
	}
	return successCount;
}

TEST(BernoulliTest, draw)
{
	double p = 0.7;
	int successCount = drawSeveralTimes(NB_ITER, p);
	double effectiveProba = (double) successCount / (double) NB_ITER;
	EXPECT_GT(effectiveProba, p*0.9);
	EXPECT_LT(effectiveProba, p*1.1);
}


TEST(BernoulliTest, zeroSuccessRate)
{
	int successCount = drawSeveralTimes(NB_ITER, 0.0);
	EXPECT_EQ(0, successCount);
}

TEST(BernoulliTest, oneSuccessRate)
{
	int successCount = drawSeveralTimes(NB_ITER, 1.0);
	EXPECT_EQ(0, successCount - NB_ITER);
}

TEST(BernoulliTest, throwIfBadProba)
{
	ASSERT_THROW(drawSeveralTimes(NB_ITER, -0.5), std::domain_error);
	ASSERT_THROW(drawSeveralTimes(NB_ITER, 1.5), std::domain_error);
}






