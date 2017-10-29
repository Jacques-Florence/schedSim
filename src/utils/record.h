/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef RECORD_H
#define RECORD_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <utils/configuration.h>

namespace Utils
{

class Record
{
public:
	Record(std::shared_ptr<Utils::Configuration> conf, std::string name);
	void add(double time, double element);
	void printToFile(std::string folder) const;
private:
	std::vector<std::pair<double, double>> vector;
	std::string name;
	std::shared_ptr<Utils::Configuration> conf;
	bool record{true};
};


}

#endif
