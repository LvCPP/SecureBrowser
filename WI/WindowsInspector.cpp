#include "WindowsInspector.h"
#include "TlHelp32.h"

using namespace SBWindowsInspector;
using namespace BrowserLogger;
using namespace Utils;

HWINEVENTHOOK window_hook_;
HINSTANCE hinst_;
MSG message_;

WindowsInspector::~WindowsInspector()
{
	StopAndWait();
}

BOOL WindowsInspector::EnumWindowsProc(HWND hwnd)
{
	char wnd_title[255];
	DWORD processid_;
	wchar_t processname[255];
	if (IsWindowEnabled(hwnd))
	{
		GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
		GetWindowThreadProcessId(hwnd, &processid_);
		HANDLE handle_ = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (handle_)
		{
			PROCESSENTRY32 pe32;
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(handle_, &pe32)) {
				do
				{
					if (processid_ == pe32.th32ProcessID)
					{
						//logdebug(*An<Logger>()) << "Title: " << wnd_title_;
						//logdebug(*An<Logger>()) << "Process Id: " << processid_;
						//logdebug(*An<Logger>()) << "Process name: " <<pe32.szExeFile;
						
						std::wcout << "Title: " << wnd_title << std::endl;
						std::wcout << "Process Id: " << processid_ << std::endl;
						std::wcout << "Process name: " << pe32.szExeFile << std::endl << std::endl;
					}
				} 
				while (Process32Next(handle_, &pe32));
			}
			CloseHandle(handle_);
		}
	}
	return true;
}


void CALLBACK WinEventProc(
	HWINEVENTHOOK	hWinEventHook
	, DWORD         event
	, HWND          hwnd
	, LONG          idObject
	, LONG          idChild
	, DWORD         dwEventThread
	, DWORD         dwmsEventTime)
{
	switch (event)
	{
	case EVENT_OBJECT_CREATE:
		OutputDebugStringA("Window Created: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_SYSTEM_MOVESIZEEND:
		OutputDebugStringA("Window Moved: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_SYSTEM_MINIMIZESTART:
		OutputDebugStringA("Window Minimized: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_SYSTEM_SWITCHEND:
		OutputDebugStringA("Window Switched: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_OBJECT_DESTROY:
		OutputDebugStringA("Window Destroyed: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_OBJECT_FOCUS:
		OutputDebugStringA("Focus on window: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	default:
		break;
	}
	
}

void WindowsInspector::MessageLoop()
{
	window_hook_ = SetWinEventHook(EVENT_MIN, EVENT_MAX, hinst_, WinEventProc, 0, 0, WINEVENT_INCONTEXT);
	while (GetMessage(&message_, NULL, 0, 0))
	{
		TranslateMessage(&message_);
		DispatchMessage(&message_);
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
	UnhookWinEvent(window_hook_);
}

void WindowsInspector::StopAndWait()
{
	StopWindowsInspector();
	if (worker_.joinable())
		worker_.join();
}