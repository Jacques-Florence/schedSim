/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "record.h"

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace Utils;

Record::Record(std::shared_ptr<Utils::Configuration> c, std::string n) : name(n), conf(c)
{
	record = conf->getBoolValue("global", "record", true);
}

void Record::printToFile(std::string folder) const
{
	if (!record)
		return;
	std::string filename = conf->getFilePrefix() + name + "Report.txt";
	std::string path = folder + "/" + filename;
	std::ofstream file;
	file.open(path, std::ios_base::app);
	file << "report for "<< name <<" ("<<vector.size()<<"entries):\n";
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		file << std::setfill(' ') << std::setw(12) << std::setprecision(12);
		file << vector[i].first << ": " << vector[i].second << "\n";
	}
	file.close();
}


void Record::add(double time, double element)
{
	if (record)
		vector.push_back(std::pair<double, double>(time, element));
}

