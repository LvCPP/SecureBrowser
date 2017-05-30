#include "WindowsInspector.h"

using namespace SBWindowsInspector;

HHOOK window_hook;
HINSTANCE hInst_ = NULL;
MSG message;

WindowsInspector::WindowsInspector()
{

}
WindowsInspector::~WindowsInspector()
{
	StopAndWait();
}

BOOL CALLBACK WindowsInspector::EnumWindowsProc()
{
	HWND hwnd = GetForegroundWindow();
	char wnd_title[255] = "";
	DWORD* processID = new DWORD;
	TCHAR processname[255];
	if (IsWindowVisible(hwnd))
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION 
			| PROCESS_VM_READ , FALSE, *processID);
		GetWindowText(hwnd, (LPWSTR)wnd_title, sizeof(wnd_title));
		GetWindowThreadProcessId(hwnd, processID);
		GetModuleBaseName(hProcess, NULL, processname, sizeof(processname));
		std::cout << wnd_title << std::endl;
		std::cout << *processID << std::endl;
		std::cout << processname << std::endl;
	}
	return true;
}

LRESULT CALLBACK WindowsInspector::CBTProc(INT code, WPARAM wparam, LPARAM lparam)
{
	if (code < 0)
		return CallNextHookEx(NULL, code, wparam, lparam);
	switch (code)
	{
	case  HCBT_ACTIVATE:
		WindowsInspector::EnumWindowsProc();
		OutputDebugStringA("Window activated\n");
		break;
	case HCBT_CREATEWND:
		OutputDebugStringA("Window created\n");
		WindowsInspector::EnumWindowsProc();
		break;
	case HCBT_DESTROYWND:
		OutputDebugStringA("Window destroyed\n");
		WindowsInspector::EnumWindowsProc();
		break;
	case HCBT_MINMAX:
		OutputDebugStringA("Window minimize or maximized\n");
		WindowsInspector::EnumWindowsProc();
		break;
	case HCBT_MOVESIZE:
		OutputDebugStringA("Window moved\n");
		break;
	case HCBT_SETFOCUS:
		OutputDebugStringA("Focus on window:\n");
		break;
	default:
		break;
	}
	return CallNextHookEx(NULL, code, wparam, lparam);
}

void WindowsInspector::MessageLoop()
{
	window_hook = SetWindowsHookEx(WH_CBT, WindowsInspector::CBTProc, GetModuleHandleA(0), 0);
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void WindowsInspector::StartWindowsInspector()
{
	worker_ = std::thread(&WindowsInspector::MessageLoop, this);
	OutputDebugStringA("WINDOWS INSPECTOR STARTED WORKING\n");
}

void WindowsInspector::StopWindowsInspector()
{
	PostThreadMessage(GetThreadId(worker_.native_handle()), WM_QUIT, 0, 0);
	OutputDebugStringA("WINDOWS INSPECTOR STOPPED WORKING\n");
	UnhookWindowsHookEx(window_hook);
}

void WindowsInspector::StopAndWait()
{
	StopWindowsInspector();
	if (worker_.joinable())
		worker_.join();
}