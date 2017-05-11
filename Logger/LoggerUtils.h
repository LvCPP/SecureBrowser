#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include <map>

#ifdef LOGGER_LIB
	#define LOGGER_API __declspec(dllexport)
#else
	#define LOGGER_API __declspec(dllimport)
#endif

namespace BrowserLogger
{

#define logerror(logger) (logger).MakeMessageBuilder(LogLevel::Error, __FILE__, __FUNCTION__, __LINE__, GetTimeStructure()) 
#define logwarning(logger) (logger).MakeMessageBuilder(LogLevel::Warning, __FILE__, __FUNCTION__, __LINE__, GetTimeStructure()) 
#define loginfo(logger) (logger).MakeMessageBuilder(LogLevel::Info, __FILE__, __FUNCTION__, __LINE__, GetTimeStructure()) 
#define logdebug(logger) (logger).MakeMessageBuilder(LogLevel::Debug, __FILE__, __FUNCTION__, __LINE__, GetTimeStructure()) 

static tm GetTimeStructure()
{
	time_t time_now = time(nullptr);
	tm local_time_now;
	localtime_s(&local_time_now, &time_now);
	return local_time_now;
}

static std::string GetFormattedTime(tm time)
{
	std::stringstream time_stream;
	time_stream << std::put_time(&time, "%T");
	return time_stream.str();
}

static std::string GetFormattedDate(tm time)
{
	std::stringstream time_stream;
	time_stream << std::put_time(&time, "%d/%m/%y");
	return time_stream.str();
}

enum class LogLevel
{
	Debug,
	Info,
	Warning,
	Error,
};

struct LogMessage
{
	std::string message;
	LogLevel level;
	std::string file;
	std::string function;
	unsigned int line;
	tm time;
};

static const std::map<LogLevel, std::string> log_level_name{ { LogLevel::Debug, "Debug" }
,{ LogLevel::Info, "Info" }
,{ LogLevel::Warning, "Warning" }
,{ LogLevel::Error, "Error" } };

static std::string DefaultFormat(const LogMessage& log_message)
{
	std::stringstream formatted_message;
	formatted_message << "[Function: " << log_message.function << "] [Line: " << log_message.line 
		<< "] [" << GetFormattedDate(log_message.time) << " at " << GetFormattedTime(log_message.time) << "]" << " ["
		<< log_level_name.at(log_message.level) << "] " << log_message.message << std::endl;
	return formatted_message.str();
}

} // namespace BrowserLogger