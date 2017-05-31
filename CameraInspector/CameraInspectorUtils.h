#pragma once

#ifdef CI_LIB
	#define CI_API __declspec(dllexport)
#else
	#define CI_API __declspec(dllimport)
#endif