#pragma once
#include "WindowsInspectorUtils.h"
#include "WindowsInspectorData.h"
#include <Logger.h>
#include <thread>
#include <windows.h>
#include <iostream>
#include <fstream>


namespace SBWindowsInspector
{

enum class WindowsEvents
{
	WindowCreated,
	WindowMoved,
	WindowMinimized,
	WindowSwitched,
	WindowDestroyed,
	WindowFocusChanged
};


class WindowsInspector /*: public WindowsInspectorObserver*/
{
public:
	WINDOWSINSPECTOR_API ~WindowsInspector();

	WINDOWSINSPECTOR_API void StartWindowsInspector();
	WINDOWSINSPECTOR_API void StopWindowsInspector();
	void StopAndWait();
	static WindowsData WindowInfo(HWND hwnd);

protected:
	void MessageLoop();

private:
	std::thread worker_;

};

} // namespace SBWindowsInspector