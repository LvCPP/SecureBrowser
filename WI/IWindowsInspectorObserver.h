#pragma once
#include "windows.h"

namespace SBWindowsInspector
{
class IWindowsInspectorObserver
{
public:
	virtual  ~IWindowsInspectorObserver() = default;
	virtual void OnWindowChanged(char wnd_title, DWORD processID, wchar_t processname) = 0;
};
}
