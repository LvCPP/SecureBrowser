#pragma once
#include "WindowsInspectorUtils.h"
#include <atomic>
#include <thread>
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>

namespace SBWindowsInspector
{

class WindowsInspector
{
public:
	WINDOWSINSPECTOR_API WindowsInspector();
	WINDOWSINSPECTOR_API ~WindowsInspector();

	WINDOWSINSPECTOR_API void StartWindowsInspector();
	WINDOWSINSPECTOR_API void StopWindowsInspector();
	void StopAndWait();
	static LRESULT CALLBACK CBTProc(INT code, WPARAM wparam, LPARAM lparam);
	static BOOL CALLBACK EnumWindowsProc();

protected:
	void MessageLoop();

private:
	std::thread worker_;

};

}