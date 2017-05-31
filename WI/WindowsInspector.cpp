#include "WindowsInspector.h"

using namespace SBWindowsInspector;

HWINEVENTHOOK window_hook;
//HHOOK window_hook = NULL;
HINSTANCE hInst_;
MSG message;

WindowsInspector::WindowsInspector()
{

}
WindowsInspector::~WindowsInspector()
{
	StopAndWait();
}

BOOL CALLBACK WindowsInspector::EnumWindowsProc(HWND hwnd)
{
	char wnd_title[255] = "";
	DWORD* processID = new DWORD;
	/*LPSTR processname;*/
	char processname[255] = "";
	if (IsWindowEnabled(hwnd))
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION 
			| PROCESS_VM_READ , FALSE, *processID);
		GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
		GetWindowThreadProcessId(hwnd, processID);
		GetModuleBaseNameA(hProcess, NULL, processname, sizeof(processname));
		//OutputDebugStringA(wnd_title.c_str());
		std::cout << wnd_title << std::endl;
		std::cout << *processID << std::endl;
		std::cout << processname << std::endl;
	}
	return true;
}

void CALLBACK WinEventProc(
	HWINEVENTHOOK hWinEventHook,
	DWORD         event,
	HWND          hwnd,
	LONG          idObject,
	LONG          idChild,
	DWORD         dwEventThread,
	DWORD         dwmsEventTime
)
{
	switch (event)
	{
	case EVENT_OBJECT_CREATE:
		OutputDebugStringA("Create: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_SYSTEM_MOVESIZEEND:
		OutputDebugStringA("Moved: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_SYSTEM_MINIMIZEEND:
		OutputDebugStringA("Minimized: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_SYSTEM_SWITCHEND:
		OutputDebugStringA("Switched: \n");
		WindowsInspector::EnumWindowsProc(hwnd);
		break;
	case EVENT_OBJECT_DESTROY:
		OutputDebugStringA("Destroyed: \n");
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
	window_hook = SetWinEventHook(EVENT_MIN, EVENT_MAX, hInst_, WinEventProc, 0, 0, WINEVENT_INCONTEXT);
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
	UnhookWinEvent(window_hook);
}

void WindowsInspector::StopAndWait()
{
	StopWindowsInspector();
	if (worker_.joinable())
		worker_.join();
}