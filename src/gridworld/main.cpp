/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <mdp/mdpModel.h>
#include <mdp/builder.h>
#include <mdp/mdpConfiguration.h>


#include "actions.h"
#include "stateSpaceDimensions.h"
#include "domainModel.h"


using namespace Gridworld;






Mdp::MdpModel *buildMdpModel()
{
	const size_t xSize = 8;
	const size_t ySize = 5;

	std::shared_ptr<DomainModel> domainModel = std::make_shared<DomainModel>();
	Mdp::Builder builder(domainModel);
	builder.addAction(new Up());
	builder.addAction(new Down());
	builder.addAction(new Left());
	builder.addAction(new Right());
	builder.addDimension(XDimension(xSize));
	builder.addDimension(YDimension(ySize));
	
	std::shared_ptr<Mdp::MdpConfiguration> conf = std::make_shared<Mdp::MdpConfiguration>();
	
	Mdp::MdpModel model = new Mdp::MdpModel(builder.getStateSpace(), getActionSpace(), conf);
	model->init();
	return model;
}


int main()
{
	Mdp::MdpModel mdpModel = buildMdpModel();


	for (int i = 0, Mdp::action *action = nullptr; i < 10000; i++)
	{
		action = mdpModel->selectAction();
		action->performAction();
	}





	mdpModel.end();
	delete mdpModel;
	return 0;
}


















