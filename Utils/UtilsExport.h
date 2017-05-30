#pragma once

#ifndef UTILS_LIB
	#define UTILS_API __declspec(dllexport)
#else
	#define UTILS_API __declspec(dllimport)
#endif