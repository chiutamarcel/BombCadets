#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <fstream>
#include <ctime>
#include <iostream>

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance()
{
	if (instance == nullptr)
		instance = new Logger();
	return instance;
}

void Logger::log(LogLevel level, std::string message)
{
	std::ofstream logFile("log.log", std::ios::app);

	std::time_t t = std::time(nullptr);
	std::tm* localTime = std::localtime(&t);
	char timeAsString[100];
	std::strftime(timeAsString, 100, "%Y-%m-%d %H:%M:%S", localTime);
	
	logFile << "[" << timeAsString << "] ";
	
	switch (level)
	{
	case LogLevel::INFO:
		logFile << "[INFO] ";
		break;
	case LogLevel::WARNING:
		logFile << "[WARNING] ";
		break;
	case LogLevel::ERROR:
		logFile << "[ERROR] ";
		break;
	}

	logFile << message << std::endl;

	logFile.close();
}