/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace Utils
{

class Log
{
public:
	enum Color{normal, red, blue, green, lightBlue};
	template<typename T> void print(T);
	void print(Log::Color);
private:
	std::ostream& outstream = std::cout;
};



template<typename T>
void Log::print(T data)
{
        outstream << data;
}


template<typename T>
Log& operator<<(Log& log, T data)
{
	log.print(data);
	return log;
}

}
#endif

