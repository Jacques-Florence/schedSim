/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <mdp/learning/reinforcementLearning/actionValuesFunction/polynomialNetwork.h>

TEST(PolynomialNetworkTest, TestGetOutput)
{
	size_t I = 2;
	size_t O = 1;
	size_t H = 3;
	Mdp::PolynomialNetwork pol(nullptr, I, O, H);
	auto  inputWeights = std::vector<std::vector<double>>(I+1, std::vector<double>(H));
	auto outputWeights = std::vector<std::vector<double>>(H, std::vector<double>(O));
	inputWeights[0][0] = 1.0;
	inputWeights[0][1] = 1.0;
	inputWeights[0][2] = 1.0;
	inputWeights[1][0] = 1.0;
	inputWeights[1][1] = 1.0;
	inputWeights[1][2] = 1.0;
	inputWeights[2][0] = 1.0;
	inputWeights[2][1] = 1.0;
	inputWeights[2][2] = 1.0;

	outputWeights[0][0] = 1.0;
	outputWeights[1][0] = 1.0;
	outputWeights[2][0] = 1.0;

	pol.initializeWeights(inputWeights, outputWeights);

	std::vector<double> input{4.0, 5.0};

	std::vector<double> out = pol.getOutput(input);
	double actualOutput = out[0];
	std::vector<double> hidden = std::vector<double>(H, 0.0);
	
	double expectedOutput = 1.0 + 10.0 + 100.0;
	EXPECT_DOUBLE_EQ(expectedOutput, actualOutput);
}











