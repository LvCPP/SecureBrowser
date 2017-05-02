#pragma once

#ifdef KEYDLL_EXPORTS
#define KEY_API __declspec(dllexport)
#else
#define KEY_API __declspec(dllimport)
#endif