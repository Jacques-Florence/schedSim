/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef COUNTING_WHEEL_H
#define COUNTING_WHEEL_H

namespace Utils
{

class CountingWheel
{
public:
	CountingWheel(unsigned int base);
	void initialize();
	bool increment();
	unsigned int getValue();
	unsigned int getBase();
private:
	unsigned int base;
	unsigned int value{0};
};

}

#endif
