#pragma once
#include "windows.h"

namespace SBWindowsInspector
{
class IWindowsInspectorObserver
{
public:
	virtual  ~IWindowsInspectorObserver() = default;
	virtual void OnWindowChanged(char wnd_title_, DWORD processid_, wchar_t processname_) = 0;
};
}
