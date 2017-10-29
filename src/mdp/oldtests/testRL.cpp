/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <iostream>
#include <vector>


#include <mdp/mdpModel.h>
#include <mdp/stateSpaceBuilder.h>
#include <mdp/actionSpaceBuilder.h>
#include <mdp/mdpConfiguration.h>
#include <mdp/action.h>

#include "rlTestDomainModel.h"
#include "rlTestActions.h"
#include "rlTestDimensions.h"

int main()
{
	Mdp::StateSpaceBuilder stateSpaceBuilder;
	Mdp::ActionSpaceBuilder actionSpaceBuilder;

	std::shared_ptr<RlTestDomainModel> domainModel = std::make_shared<RlTestDomainModel>();

	stateSpaceBuilder.setDomainModel(domainModel);
	actionSpaceBuilder.setDomainModel(domainModel);
	
	stateSpaceBuilder.addDimension(new RlDim(12));
	stateSpaceBuilder.addDimension(new RlDim(4));

	Mdp::StateSpace *stateSpace = stateSpaceBuilder.getStateSpace();	
	
	actionSpaceBuilder.addAction(new GoUp);
	actionSpaceBuilder.addAction(new GoDown);
	actionSpaceBuilder.addAction(new GoLeft);
	actionSpaceBuilder.addAction(new GoRight);

	Mdp::ActionSpace *actionSpace = actionSpaceBuilder.getActionSpace();


	Mdp::MdpConfiguration *config = new Mdp::MdpConfiguration("configuration.conf");
	Mdp::MdpModel mdpModel(stateSpace, actionSpace, config);
	mdpModel.init();

	const int nbOfEpisodes = 500;
	const int averageHorizon = 10;
	double history[averageHorizon];
	for (int i = 0; i < nbOfEpisodes; i++)
	{
		double reward = 0.0;
		int steps = 0;
			Mdp::Action *action = mdpModel.selectActionWithoutUpdate();
			action->performAction();
			reward += domainModel->measureReward();
		while(domainModel->xpos != 11 || domainModel->ypos != 0)
		{
			steps++;
			Mdp::Action *action = mdpModel.selectAction();
			action->performAction();
			reward += domainModel->measureReward();
			//std::cout << "landed in xpos "<<domainModel->xpos<<" ypos "<<domainModel->ypos<<" \n";
		}
		mdpModel.end();
		//std::cout << "episode "<<i<<": total reward is "<<reward<<" reached in "<<steps<<" steps\n";
		history[i % averageHorizon] = reward;
		if (i >= averageHorizon)
		{
			double average = 0;
			for (int j = 0; j < averageHorizon; j++)
			{
				average += history[j];
			}
			std::cout << "episode "<<i<<": average cost: " << average/averageHorizon << "\n";
		}
		//mdpModel.printPolicy(std::cout);
		domainModel->xpos = 0;
		domainModel->ypos = 0;
	}
#if 0
		while(domainModel->xpos != 11 || domainModel->ypos != 0)
		{
			std::cout << "xpos: "<<domainModel->xpos<<"ypos:"<<domainModel->ypos<<"\n";
			Mdp::Action *action = mdpModel.selectAction();
			action->performAction();
		}
#endif
	return 0;
}
