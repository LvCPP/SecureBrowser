#pragma once

#ifdef LOGIN_LIB
#define LOGIN_API __declspec(dllexport)
#else
#define LOGIN_API __declspec(dllimport)
#endif
