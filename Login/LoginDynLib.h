#pragma once
#include <QtCore/qglobal.h>

namespace BrowserLogin
{
#ifdef LOGIN_LIB
#define LOGIN_API __declspec(dllimport)
#else
#define LOGIN_API __declspec(dllexport)
#endif
}