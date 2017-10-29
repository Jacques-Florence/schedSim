/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "math.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace Utils
{

int lcm(std::vector<int> array)
{
	size_t size = array.size();
	int result = 0;
	std::vector<int> array2 = array;
	int min;
	while(1)
	{
		min = array2[0];
		bool allEqual = true;
		for (size_t i = 1; i < size; i++)
		{
			if (array2[i] != array2[i-1])
				allEqual = false;
			if (array2[i] < min)
				min = array2[i];
		}
		if (allEqual)
		{
			result = array2[0];
			break;
		}
		for (size_t i = 0; i < size; i++)
		{
			if (array2[i] == min)
				array2[i] += array[i];
		}
	}
	return result;
}

int gcd(std::vector<int> /*array*/)
{
	/*TODO....*/
	assert(false);
	return 0;
}


}

