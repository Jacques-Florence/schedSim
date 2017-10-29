/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef GIBBS_ACTION_SELECTION_H
#define GIBBS_ACTION_SELECTION_H

#include "actionSelectionStrategy.h"

namespace Mdp
{

class GibbsActionSelection : public ActionSelectionStrategy
{
public:
	GibbsActionSelection(double temperature, double tempDecaySpeed, double tempStepSize);
	std::vector<double> generatePolicy(const std::vector<double>&, action_t bestAction) override;
private:
	void updateTemperature();
	double temperature{1.0};
	double tempDecaySpeed{1.0};
	double tempStepSize{10000};
};

}

#endif /*GIBBS_ACTION_SELECTION_H*/
