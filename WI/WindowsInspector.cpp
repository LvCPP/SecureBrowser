#include "WindowsInspector.h"
#include <string>

//using namespace WindowsInspector;

HHOOK llCBTHookHandle;
HINSTANCE _hInst = NULL;
std::thread worker_;

BOOL CALLBACK /*WI::*/EnumWindowsProc()
{
	HWND hwnd = GetForegroundWindow(); //get handle of currently active window
	char wnd_title[255] = "";
	DWORD* processID = new DWORD;
	TCHAR processname[255];
	if (IsWindowVisible(hwnd)) // check whether window is visible
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, *processID);
		GetWindowText(hwnd, (LPWSTR)wnd_title, sizeof(wnd_title));
		GetWindowThreadProcessId(hwnd, processID);
		GetModuleBaseName(hProcess, NULL, processname, sizeof(processname));
		std::cout << wnd_title << std::endl;
		std::cout << *processID << std::endl;
		std::cout << processname << std::endl;
	}
	return true; // function must return true if you want to continue enumeration
}

LRESULT CALLBACK /*WI::*/CBTProc(INT code, WPARAM wparam, LPARAM lparam)
{
	//while(is_working_)
	if (code < 0)
		return CallNextHookEx(NULL, code, wparam, lparam);
	switch (code)
	{
	case  HCBT_ACTIVATE:
		EnumWindowsProc();
		OutputDebugStringA("Window activated\n");
		break;
	case HCBT_CREATEWND:
		OutputDebugStringA("Window created\n");
		EnumWindowsProc();
		break;
	case HCBT_DESTROYWND:
		OutputDebugStringA("Window destroyed\n");
		EnumWindowsProc();
		break;
	case HCBT_MINMAX:
		OutputDebugStringA("Window minimize or maximized\n");
		EnumWindowsProc();
		break;
	case HCBT_MOVESIZE:
		OutputDebugStringA("Window moved\n");
		break;
	case HCBT_SETFOCUS:
		OutputDebugStringA("Focus on window:\n");
		break;
	case HCBT_SYSCOMMAND:
		break;
	default:
		break;
	}
	return CallNextHookEx(NULL, code, wparam, lparam);

}

bool /*WI::*/installHook()
{
	llCBTHookHandle = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTProc, GetModuleHandle(0), 0/*GetCurrentThreadId()*/);
	return llCBTHookHandle != NULL;
}

//void StartWindowsInspector()
//{
//OutputDebugStringA("WINDOWS INSPECTOR STARTED WORKING\n");
////if (!is_working_)
////{
////is_working_ = true;
//worker_ = std::thread(&CBTProc);
//}
//
//
//void StopWindowsInspector()
//{
//OutputDebugStringA("WINDOWS INSPECTOR STARTED WORKING\n");
////if (is_working_)
////{
////is_working_ = false;
//if (worker_.joinable())
//worker_.join();
//}



