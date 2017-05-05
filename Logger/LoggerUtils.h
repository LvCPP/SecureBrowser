#pragma once
#include <string>
#include <iomanip>
#include <sstream>

namespace BrowserLogger
{

#ifdef LOGGER_LIB
	#define LOGGER_API __declspec(dllexport)
#else
	#define LOGGER_API __declspec(dllimport)
#endif

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

} // namespace BrowserLogger