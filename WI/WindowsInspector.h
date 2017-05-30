#pragma once
#pragma once
#include <atomic>
#include <thread>
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>
#include "WindowsInspectorUtils.h"

//namespace WindowsInspector
//{
//
//class WI
//{
//public:
//void StartWindowsInspector();
//void StopWindowsInspector();
WINDOWSINSPECTOR_API LRESULT CALLBACK CBTProc(INT code, WPARAM wparam, LPARAM lparam);
WINDOWSINSPECTOR_API bool installHook();
WINDOWSINSPECTOR_API BOOL CALLBACK EnumWindowsProc();

//private:
//	std::atomic<bool> is_working_;
//	std::thread worker_;
//
//
//};
//
//}