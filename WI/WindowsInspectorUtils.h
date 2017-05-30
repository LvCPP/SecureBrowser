#pragma once

#ifdef WINDOWSINSPECTOR_LIB
#define WINDOWSINSPECTOR_API __declspec(dllimport)
#else
#define WINDOWSINSPECTOR_API __declspec(dllexport)
#endif
