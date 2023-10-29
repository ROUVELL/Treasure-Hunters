#include <string>
#include <iostream>

#include "Logger.h"

void Logger::setLevel(Level level)
{
	if (level >= Level::DEBUG && level <= Level::ERROR)
		Logger::level = level;
}

void Logger::log(Level level, const std::string& msg)
{
	if (level < Logger::level)
		return;

	if (level == Level::ERROR)
	{
		std::cerr << strLevels[(short)level] << msg << "\n";
		return;
	}

	std::cout << strLevels[(short)level] << msg << "\n";
}

const char* Logger::strLevels[4] =
{
	"DEBUG::", "INFO::", "WARNING::", "ERROR::"
};
Logger::Level Logger::level = Logger::Level::DEBUG;