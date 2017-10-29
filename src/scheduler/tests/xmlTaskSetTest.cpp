/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <scheduler/xmlTaskSet.h>

#include <scheduler/xmlTaskSet.h>
#include <scheduler/process.h>


TEST(XmlTaskSetTest, testXmlTaskSet)
{
	Scheduler::XmlTaskSet xml;
	std::shared_ptr<std::vector<std::shared_ptr<Scheduler::Process>>>
		vect = xml.getRealTimeTaskSetFromXml("taskset.xml");
	ASSERT_EQ((size_t) 2, vect->size());
	std::shared_ptr<Scheduler::Process> task = (*vect)[0];
	EXPECT_DOUBLE_EQ(1.2, task->powerCoeff);
	EXPECT_EQ(0, task->getPriority());
	EXPECT_DOUBLE_EQ(10.0, task->getPeriod());
	EXPECT_DOUBLE_EQ(8.0, task->getDeadline());
	EXPECT_DOUBLE_EQ(3.0, task->getWcet());

	task = (*vect)[1];
	EXPECT_DOUBLE_EQ(1.0, task->powerCoeff);
	EXPECT_DOUBLE_EQ(0, task->getPriority());
	EXPECT_DOUBLE_EQ(8.0, task->getPeriod());
	EXPECT_DOUBLE_EQ(7.0, task->getDeadline());
	EXPECT_DOUBLE_EQ(4.0, task->getWcet());
	
}
