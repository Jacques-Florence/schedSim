/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "configuration.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace Utils;

Configuration::Configuration(std::string file) : filename(file)
{
	std::cout << "Creating a configuration from file "<< filename<<"\n";
}

Configuration::~Configuration()
{
}



std::string Configuration::getStringValue(std::string section, std::string key)
{
	std::string result = "";
	stream.open(filename);
	if (!stream.is_open())
		throw std::runtime_error("cannot open file");
	std::string line;
	while(std::getline(stream, line))
	{
		if (isNewSection(line) && isMatchingSection(line, section))
			break;
	}
	key = key + " = ";
	while(std::getline(stream, line))
	{
		if (isNewSection(line))
			break;
		if (!line.compare(0, key.length(), key))
		{
			result = line.substr(key.length());
		}
	}
	stream.close();
	return result;
}


std::vector<std::string> Configuration::getStringList(std::string section, std::string key)
{
	std::vector<std::string> result;
	std::string list = getStringValue(section, key);
	char *charList = new char[list.size()]; //I'm sure there is an easier way to do all that...
	//TODO what about using Utils::StringUtils::split()
	charList = strcpy(charList, list.c_str());
	char *token;
	token = strtok(charList, " ");
	while(token != NULL)
	{
		result.push_back(token);
		token = strtok(NULL, " ");
	}
	delete[] charList;
	return result;
}



bool Configuration::isNewSection(std::string line)
{
	return line[0] == '[';
}

bool Configuration::isMatchingSection(std::string line, std::string section)
{
	section = "[" + section + "]";
	int result = line.compare(section);
	return result == 0;
}






double Configuration::getDoubleValue(std::string section, std::string key)
{
	std::string str = getStringValue(section, key);
	return std::stod(str, nullptr);
}




int Configuration::getIntValue(std::string section, std::string key)
{
	std::string str = getStringValue(section, key);
	int result = std::stoi(str, nullptr);
	return result;
}


unsigned long long int Configuration::getUnsignedLongLongIntValue(std::string section, std::string key)
{
	std::string str = getStringValue(section, key);
	unsigned long long int result = 0;
	result = stoull(str);
	return result;
}


bool Configuration::getBoolValue(std::string section, std::string key, bool defaultValue)
{
	std::string str = getStringValue(section, key);
	if (!str.compare("yes") || !str.compare("1") || !str.compare("true" ))
		return true;
	if (!str.compare("no" ) || !str.compare("0") || !str.compare("false"))
		return false;
	return defaultValue;
}

std::string Configuration::getFilePrefix()
{
	std::string prefix = filename;
	prefix = stripDirectories(prefix);
	return prefix;
}


std::string Configuration::stripDirectories(std::string str)
{
	size_t pos;
	while((pos = str.find('/')) != std::string::npos)
	{
		str = str.substr(pos + 1, std::string::npos);
	}
	return str;
}





