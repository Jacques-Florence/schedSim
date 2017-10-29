/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TABULAR_ACTION_VALUES_H
#define TABULAR_ACTION_VALUES_H

#include "actionValuesFunction.h"

#include <string>
#include <vector>

#include <mdp/context.h>

namespace Mdp
{

class TabularActionValues : public ActionValuesFunction
{
public:
	TabularActionValues(std::shared_ptr<Context> context);
	std::vector<std::vector<double>> randomly(size_t S, size_t A, time_t seed, double lowerBound, double upperBound);
	std::vector<std::vector<double>> uniformly(size_t S, size_t A, double initialActionValues);
	std::vector<std::vector<double>> fromFile(size_t S, size_t A, std::string filename);
	double getValue(state_t state, action_t action) override;
	std::vector<double> getValues(state_t state) override;
	void updateValue(state_t state, action_t action, double value);
	size_t size();
protected:
	void init(std::shared_ptr<Context> context);
	std::vector<std::vector<double>> actionValues;
};

}
#endif
