/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace Utils
{

class StringUtils
{
public:
	static std::vector<std::string> split(std::string str, char delimiter);
};


}

#endif
