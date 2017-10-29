/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <chrono>
#include <ctime>

namespace Utils
{

class ProgramTime
{
public:
	static void init();
	static double elapsedTimeInSeconds();
private:
	static clock_t tp;
};

}


