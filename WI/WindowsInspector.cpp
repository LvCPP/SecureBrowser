#include "WindowsInspector.h"
#include "TlHelp32.h"

using namespace SBWindowsInspector;

HWINEVENTHOOK window_hook;
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
	char wnd_title[255];
	DWORD processID;
	wchar_t processname[255];
	if (IsWindowEnabled(hwnd))
	{
		GetWindowTextA(hwnd, wnd_title, sizeof(wnd_title));
		GetWindowThreadProcessId(hwnd, &processID);
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnapshot)
		{
			PROCESSENTRY32 pe32;
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (Process32First(hSnapshot, &pe32)) {
				do
				{
					if (processID == pe32.th32ProcessID)
					{
					std::cout << "Tittle: " << wnd_title << std::endl;
					std::cout << "Process Id: " << processID << std::endl;
					std::wcout << "Process name: " <<pe32.szExeFile << std::endl;
					}
				} 
				while (Process32Next(hSnapshot, &pe32));
			}
			CloseHandle(hSnapshot);
		}
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
	case EVENT_SYSTEM_MINIMIZESTART:
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