#pragma once

#ifdef KEYDLL_LIB
#define KEY_API __declspec(dllexport)
#else
#define KEY_API __declspec(dllimport)
#endif