#pragma once

#ifdef LOGIN2_LIB
#define LOGIN2_API __declspec(dllexport)
#else
#define LOGIN2_API __declspec(dllimport)
#endif
