/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include "log.h"

#include <iostream>

using namespace Utils;


void Log::print(Log::Color color)
{
#ifdef __linux__
	if (outstream.rdbuf() != std::cout.rdbuf())
	{
		return;
	}
        switch (color)
        {
                case Log::Color::red:
                        outstream << "\033[1;31m";
                        break;
                case Log::Color::green:
                        outstream << "\033[1;32m";
                        break;
                case Log::Color::blue:
                        outstream << "\033[1;34m";
                        break;
                case Log::Color::normal:
                        outstream << "\033[0m";
			break;
		case Log::Color::lightBlue:
			outstream << "\033[34m";
			break;
                default:
                        outstream << "";
                        break;
        }
#endif
}













