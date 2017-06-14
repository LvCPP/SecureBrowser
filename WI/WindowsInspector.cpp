#include "WindowsInspector.h"
#include "IWindowsInspectorObserver.h"
#include "WindowsInspectorObserver.h"
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

WindowsData WindowsInspector::WindowInfo(HWND hwnd)
{
	char wnd_title[255];
	DWORD processid_;
	WindowsData data(hwnd);
	if (IsWindowEnabled(hwnd))
	{
		GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
		GetWindowThreadProcessId(hwnd, &processid_);
		if (wnd_title[0] != '\0')
		{
			HANDLE handle_ = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (handle_)
			{
				PROCESSENTRY32 pe32;
				pe32.dwSize = sizeof(PROCESSENTRY32);
				if (Process32First(handle_, &pe32))
				{
					do
					{
						if (processid_ == pe32.th32ProcessID)
						{
							//logdebug(*An<Logger>()) << "Title: " << wnd_title_;
							//logdebug(*An<Logger>()) << "Process Id: " << processid_;
							//logdebug(*An<Logger>()) << "Process name: " <<pe32.szExeFile;

							ShowWindow(hwnd, SW_MINIMIZE);

							std::cout << "Title: " << wnd_title << std::endl;
							std::cout << "Process Id: " << processid_ << std::endl;
							std::cout << "Process name: " << pe32.szExeFile << std::endl << std::endl;
							data.SetTitle(wnd_title);
							data.SetProcessId(processid_);
							data.SetProcessName(pe32.szExeFile);
						}
					}
					while (Process32Next(handle_, &pe32));
				} 
			}
			CloseHandle(handle_);
		}
	}
	return data;
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
	WindowsInspectorObserver wd_obs;
	if (hwnd != GetAncestor(hwnd, GA_ROOTOWNER))
		return;
	switch (event)
	{
	case EVENT_OBJECT_CREATE:
		OutputDebugStringA("Window Created: \n");
		//ShowWindow(hwnd, SW_MINIMIZE);
		wd_obs.Notify(WindowsEvents::WindowCreated, WindowsData(hwnd)/*WindowsInspector::WindowInfo(hwnd)*/);
		break;

	//case EVENT_SYSTEM_MOVESIZEEND:
	//	OutputDebugStringA("Window Moved: \n");
	//	WindowsInspector::WindowInfo(hwnd);
	//	ShowWindow(hwnd, SW_MINIMIZE);
	//	break;
	//case EVENT_SYSTEM_MINIMIZESTART:
	//	OutputDebugStringA("Window Minimized: \n");
	//	WindowsInspector::WindowInfo(hwnd);
	//	ShowWindow(hwnd, SW_MINIMIZE);
	//	break;
	//case EVENT_SYSTEM_SWITCHEND:
	//	OutputDebugStringA("Window Switched: \n");
	//	WindowsInspector::WindowInfo(hwnd);
	//	ShowWindow(hwnd, SW_MINIMIZE);
	//	break;
	//case EVENT_OBJECT_DESTROY:
	//	OutputDebugStringA("Window Destroyed: \n");
	//	WindowsInspector::WindowInfo(hwnd);
	//	ShowWindow(hwnd, SW_MINIMIZE);
	//	break;
	case EVENT_OBJECT_FOCUS:
		OutputDebugStringA("Focus on window: \n");
		wd_obs.Notify(WindowsEvents::WindowFocusChanged, WindowsData(hwnd));
		WindowsInspector::WindowInfo(hwnd);
		//ShowWindow(hwnd, SW_MINIMIZE);
		break;
	default:
		break;
	}
	
}

void WindowsInspector::MessageLoop()
{
	window_hook_ = SetWinEventHook(EVENT_MIN, EVENT_MAX, hinst_, WinEventProc, 0, 0, WINEVENT_INCONTEXT | WINEVENT_SKIPOWNPROCESS);
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