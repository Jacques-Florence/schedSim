/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "stringUtils.h"

#include <string>
#include <sstream>


using namespace Utils;

std::vector<std::string> StringUtils::split(std::string str, char del)
{
	/*TODO*/

	std::vector<std::string> vector;
	std::stringstream stream(str);
	std::string element;
	while (std::getline(stream, element, del))
	{
		if (element.size() == 0)
			continue;
		vector.push_back(element);
	}
	return vector;
}




