#pragma once

#include <iostream>
#include <string>

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR,
	XXXX
};

class Logger
{
private:
	static Logger* instance;
	Logger() {};

public:
	static Logger* getInstance();

	void log(LogLevel level, std::string message);
};
