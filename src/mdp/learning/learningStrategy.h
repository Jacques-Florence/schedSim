/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef MDPLEARNINGSTRATEGY_H
#define MDPLEARNINGSTRATEGY_H

#include <memory>

namespace Mdp
{
struct Context;
struct MdpConfiguration;


class LearningStrategy
{
public:
	LearningStrategy(std::shared_ptr<Context> context);
	virtual ~LearningStrategy();
	virtual void initializeModel()=0;
	virtual void updateModel()=0;
	virtual void end(){};
protected:
	std::shared_ptr<Context> context;
};


}
#endif
