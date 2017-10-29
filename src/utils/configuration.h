/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Utils
{

class Configuration : public std::enable_shared_from_this<Configuration>
{
public:
	Configuration(std::string file);
	virtual ~Configuration();
	virtual std::string getStringValue(std::string section, std::string key);
	virtual std::vector<std::string> getStringList(std::string section, std::string key);
	virtual double getDoubleValue(std::string section, std::string key);
	virtual unsigned long long int getUnsignedLongLongIntValue(std::string section, std::string key); /*TODO: refactor all those functions into a template*/
	virtual int getIntValue(std::string section, std::string key);
	virtual bool getBoolValue(std::string section, std::string key, bool defaultValue);
	/**@brief returns the name of the configuration file stripped of any directory
	 */
	std::string getFilePrefix();
	std::string getName(){return filename;};
protected:
	std::string filename;
	std::ifstream stream;
	static bool isNewSection(std::string line);
	static bool isMatchingSection(std::string line, std::string section);
	std::string stripDirectories(std::string);
};

}

#endif
