#pragma once

#ifdef LOGINDIALOG_LIB
#define LOGIN_DIALOG_API __declspec(dllexport)
#else
#define LOGIN_DIALOG_API __declspec(dllimport)
#endif