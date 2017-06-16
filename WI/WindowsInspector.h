#pragma once
#include "WindowsInspectorUtils.h"
#include <Logger.h>
#include <thread>
#include <windows.h>

namespace SBWindowsInspector
{

class WindowsInspector
{
public:
	WINDOWSINSPECTOR_API ~WindowsInspector();

	WINDOWSINSPECTOR_API void StartWindowsInspector();
	WINDOWSINSPECTOR_API void StopWindowsInspector();
	void StopAndWait();
	static BOOL EnumWindowsProc(HWND hwnd);

protected:
	void MessageLoop();

private:
	std::thread worker_;
};

} // namespace SBWindowsInspector