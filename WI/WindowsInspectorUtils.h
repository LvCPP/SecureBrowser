#pragma once

#ifdef WINDOWSINSPECTOR_LIB
#define WINDOWSINSPECTOR_API __declspec(dllexport)
#else
#define WINDOWSINSPECTOR_API __declspec(dllimport)
#endif
