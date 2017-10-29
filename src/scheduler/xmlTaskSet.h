/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef XML_TASK_SET_H
#define XML_TASK_SET_H

#include <vector>
#include <memory>

#include <tinyxml2/tinyxml2.h>

namespace Scheduler
{

class Process;

class XmlTaskSet
{
public:
	std::shared_ptr<std::vector<std::shared_ptr<Process>>>
		getRealTimeTaskSetFromXml(std::string filename);
private:
	void getTaskData(tinyxml2::XMLElement *elem);
	std::shared_ptr<std::vector<std::shared_ptr<Process>>> taskVector;
};

}
#endif


