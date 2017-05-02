#pragma once

namespace BrowserLogger
{

#ifdef LOGGER_LIB
	#define LOGGER_API __declspec(dllexport)
#else
	#define LOGGER_API __declspec(dllimport)
#endif

} // namespace BrowserLogger