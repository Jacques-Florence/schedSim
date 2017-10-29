/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "xmlTaskSet.h"

#include <iostream>
#include <stdexcept>

#include <tinyxml2/tinyxml2.h>

#include <utils/randomGenerator.h>
#include <utils/distributions/bernoulli.h>

#include "system.h"
#include "process.h"

using namespace Scheduler;



std::shared_ptr<std::vector<std::shared_ptr<Process>>>
XmlTaskSet::getRealTimeTaskSetFromXml(std::string filename)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.LoadFile(filename.c_str());
	if (err != tinyxml2::XML_SUCCESS)
		throw std::runtime_error("could not load xml file"); //TODO: create a new exception

	tinyxml2::XMLElement *root = doc.RootElement();
	if (root == nullptr)
		throw std::runtime_error("no root node");

	tinyxml2::XMLElement *processElem = root->FirstChildElement("process");

	taskVector = std::make_shared<std::vector<std::shared_ptr<Process>>>();

	while (processElem != nullptr)
	{
		getTaskData(processElem);
		processElem = processElem->NextSiblingElement("process");
	}


	return taskVector;	
}




void XmlTaskSet::getTaskData(tinyxml2::XMLElement *elem)
{
	double releaseTime = 0.0;
	double wcet = 1.0;
	double period = 10.0;
	double deadline = 10.0;
	int pid = Process::getNewPid();
	int priority = 0;
	double bcet = 0.0;
	double powerCoeff = 1.0;
	std::shared_ptr<Utils::BoundedRandomDistribution> randomDist = nullptr;


	//FIXME release time not used
	tinyxml2::XMLElement *releaseTimeElem = elem->FirstChildElement("releaseTime");
	if (releaseTimeElem != nullptr)
	{
		releaseTimeElem->QueryDoubleText(&releaseTime);
	}
	tinyxml2::XMLElement *powerCoeffElem = elem->FirstChildElement("powerCoeff");
	if (powerCoeffElem != nullptr)
	{
		powerCoeffElem->QueryDoubleText(&powerCoeff);
	}
	tinyxml2::XMLElement *priorityElem = elem->FirstChildElement("priority");
	if (priorityElem != nullptr)
	{
		priorityElem->QueryIntText(&priority);
	}
	tinyxml2::XMLElement *periodElem = elem->FirstChildElement("period");
	if (periodElem != nullptr)
	{
		periodElem->QueryDoubleText(&period);
	}
	tinyxml2::XMLElement *deadlineElem = elem->FirstChildElement("deadline");
	if (deadlineElem != nullptr)
	{
		deadlineElem->QueryDoubleText(&deadline);
	}
	tinyxml2::XMLElement *wcetElem = elem->FirstChildElement("wcet");
	if (wcetElem != nullptr)
	{
		wcetElem->QueryDoubleText(&wcet);
	}
	tinyxml2::XMLElement *durationDistribution
		= elem->FirstChildElement("durationDistribution");
	if (durationDistribution != nullptr)
	{
		if (durationDistribution->Attribute("xsi:type", "deterministic"))
		{
			//taken care of by having a nullptr randomDist
		}
		else if (durationDistribution->Attribute("xsi:type", "bernoulli"))
		{
			tinyxml2::XMLElement *bcetElem = durationDistribution->FirstChildElement("bcet");
			tinyxml2::XMLElement *pElem = durationDistribution->FirstChildElement("p");
			bcetElem->QueryDoubleText(&bcet);
			double p;
			pElem->QueryDoubleText(&p);
			/*FIXME: where should this randomGen be created and destroyed?*/
			Utils::RandomGenerator *randomGen = new Utils::RandomGenerator;
			randomDist = std::make_shared<Utils::Bernoulli>(randomGen, p);
		}
		else
		{
			//error
		}
	}
	
	std::shared_ptr<Process> task
		= Process::createRealTimeTask(wcet, period, deadline, pid, priority, bcet);
	task->setPowerCoeff(powerCoeff);
	task->setDurationDistribution(randomDist);

	taskVector->push_back(task);
}




























