/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>
#include <vector>

namespace Utils
{

class RandomGenerator
{
public:
	RandomGenerator();
	RandomGenerator(time_t seed);
	double drawExp(double lambda);
	double drawUniform(double min, double max);
	double drawBeta(double alpha, double beta);
	int drawUniformInt(int min, int max);
	/*This function returns a vector of nbOfBins components,
	containing elements so that the total of them is 1.
	This is generating a random discrete distribution*/
	std::vector<double> drawDistribution(int nbOfBins);
	void seed(time_t seed);
private:
	std::default_random_engine gen;
	std::uniform_real_distribution<double> unif;
};

}

#endif
