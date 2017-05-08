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

static tm GetTimeStructure()
{
	time_t time_now = time(nullptr);
	tm local_time_now;
	localtime_s(&local_time_now, &time_now);
	return local_time_now;
}

static std::string GetFormattedTime()
{
	tm time = GetTimeStructure();
	std::stringstream time_stream;
	time_stream << std::put_time(&time, "%T");
	return time_stream.str();
}

static std::string GetFormattedDate()
{
	tm time = GetTimeStructure();
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
};

static const std::map<LogLevel, std::string> log_level_name{ { LogLevel::Debug, "Debug" }
,{ LogLevel::Info, "Info" }
,{ LogLevel::Warning, "Warning" }
,{ LogLevel::Error, "Error" } };

static std::string DefaultFormat(const LogMessage& log_message)
{
	std::stringstream formatted_message;
	formatted_message << "[" << GetFormattedDate() << " at " << GetFormattedTime() << "]" << " ["
		<< log_level_name.at(log_message.level) << "] " << log_message.message << std::endl;
	return formatted_message.str();
}

} // namespace BrowserLogger