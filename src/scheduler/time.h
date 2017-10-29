/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef TIME_H
#define TIME_H

namespace Scheduler
{

class Time
{
public:
	static double getTime();
	static void updateTime(double t);
	static double getEndTime();
private:
	static double time;
};

}

#endif
