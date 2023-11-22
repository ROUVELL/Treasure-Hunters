#pragma once

class Logger
{
public:
	enum class Level
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	static void setLevel(Level level);

	static void log(const char* msg) { Logger::log(std::string{msg}); }
	static void log(const std::string& msg) { Logger::log(Logger::level, msg); }

	static void logDebug(const char* msg)        { Logger::log(Level::DEBUG, msg); }
	static void logDebug(const std::string& msg) { Logger::log(Level::DEBUG, msg); }

	static void logInfo(const char* msg)        { Logger::log(Level::INFO, msg); }
	static void logInfo(const std::string& msg) { Logger::log(Level::INFO, msg); }

	static void logWarning(const char* msg)        { Logger::log(Level::WARNING, msg); }
	static void logWarning(const std::string& msg) { Logger::log(Level::WARNING, msg); }

	static void logError(const char* msg, bool _exit = true) { Logger::log(Level::ERROR, msg); if (_exit) exit(1); }
	static void logError(const std::string& msg, bool _exit = true) { Logger::log(Level::ERROR, msg); if (_exit) exit(1); }

private:
	static const char* strLevels[4];

	static Level level;

	static void log(Level level, const char* msg) { Logger::log(level, std::string{msg}); }
	static void log(Level level, const std::string& msg);
};

