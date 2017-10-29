/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <mdp/learning/reinforcementLearning/actionValuesFunction/neuralNetwork.h>
#include <vector>
#include <utils/randomGenerator.h>

#include <iostream>

#include "doublefann.h"

TEST(NeuralNetworkTest, nnTest)
{
#if 0
	Utils::RandomGenerator gen;
	Mdp::NeuralNetwork net(1, 100, 1);
	/*Let's train a square function*/
	size_t nbSamples = 100000;
	for (size_t i = 0; i < nbSamples; i++)
	{
		double x = gen.drawUniform(-10.0, 10.0);
		std::cout << "MSE: "<< net.getMse() <<"\n";
		net.learnExample(std::vector<double>(1, x), std::vector<double>(1, x*x));
	}
	for (int i = 0; i < 10; i++)
	{
		std::vector<double> in(1, (double)i);
		std::vector<double> out = net.getOutput(in);
		double output = out[0];
		std::cout << "i="<<i<<" i*i = "<< output <<"\n";
	}
#endif

#if 1
	size_t length = 10000;
	size_t nbEpochs = 100;
	Utils::RandomGenerator gen;
	struct fann *ann = fann_create_standard(3, 1, 4, 1);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID);
	fann_set_activation_function_output(ann, FANN_LINEAR);
	fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
	fann_set_train_error_function(ann, FANN_ERRORFUNC_LINEAR);
	fann_set_learning_rate(ann, 0.5);
	fann_set_activation_steepness_hidden(ann, 0.5);

	std::vector<double> xs(length);
	std::vector<double> ys(length);

	for (size_t i = 0; i < length; i++)
	{
		double x = gen.drawUniform(-1.0, 1.0);
		xs[i] = x;
		ys[i] = x*x;
	}

	for (size_t i = 0; i < nbEpochs; i++)
	{
		for (size_t j = 0; j < length; j++)
		{
			double x = xs[j];
			double y = ys[j];
			fann_train(ann, &x, &y);
		}
	}


	for (double i = -1.0; i < 1.0; i += 0.05)
	{
		double x = i;
		double *out = fann_run(ann, &x);
		std::cout << "x: "<< x <<" y: "<< *out <<"\n";
	}
	//fann_print_connections(ann);

	fann_destroy(ann);
#endif





#if 0
	int NUM_ITERATIONS = 10000;
    struct fann *ann;
    fann_type d1[1] = { 0.5 };
    fann_type d2[1] = { 0.0 };
    fann_type *pres;
    int i;

    /* Create network */
    ann = fann_create_standard(3, 1, 4, 1);

    /* 
     * Train network 
     * input: 0.0 => output: 0.5
     * input: 0.5 => output: 0.0
     */
    i = NUM_ITERATIONS;
    while (--i)
    {
        fann_train(ann, d1, d2);
        fann_train(ann, d2, d1);
    }

    /* Should return 0.5 */
    pres = fann_run(ann, d2);
    printf("%f\n", pres[0]);

    /* Should return 0.0 */
    pres = fann_run(ann, d1);
    printf("%f\n", pres[0]);

    /* Destroy network */
    fann_destroy(ann);
#endif


}

























