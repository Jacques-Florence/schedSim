/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef COUNTER_H
#define COUNTER_H

#include "countingWheel.h"

#include <vector>

namespace Utils
{

/**This is a counter with multiple bases: each digit has a different base*/
class Counter
{
public:
	~Counter();
	void addWheel(unsigned int base);
	void initialize();
	bool increment();
	std::vector<unsigned int> getValue();
	/*The number of different values that the counter is able to produce*/
	long long unsigned int getNumberOfValues();
private:
	/*wheels[0] is the "LSB" wheel*/
	std::vector<CountingWheel*> wheels;
};

}

#endif
