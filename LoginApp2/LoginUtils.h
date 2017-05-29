#pragma once

#ifdef LOGIN2APP_LIB
#define LOGIN2APP __declspec(dllexport)
#else
#define LOGIN2APP __declspec(dllimport)
#endif