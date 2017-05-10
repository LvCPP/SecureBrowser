#pragma once
#include <QtCore/qglobal.h>

#ifdef LOGIN_LIB
#define LOGIN_API __declspec(dllexport)
#else
#define LOGIN_API __declspec(dllimport)
#endif