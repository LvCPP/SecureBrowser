#include "WindowsInspector.h"
#include "IWindowsInspectorObserver.h"
#include "WindowsInspectorObserver.h"
#include "TlHelp32.h"
#include <algorithm>

using namespace SBWindowsInspector;
using namespace BrowserLogger;
using namespace Utils;

HWINEVENTHOOK window_hook_;
HINSTANCE hinst_;
MSG message_;

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

							auto processname = pe32.szExeFile;

							std::cout << "Title: " << wnd_title << std::endl;
							std::cout << "Process Id: " << processid_ << std::endl;
							std::cout << "Process name: " << processname << std::endl << std::endl;

							//data.SetTitle(wnd_title);
							//data.SetProcessId(processid_);
							//data.SetProcessName(processname);
						}
					} while (Process32Next(handle_, &pe32));
				} 
			}
			CloseHandle(handle_);
		}
	}
	return data;
}

void WindowsInspector::Attach(const std::shared_ptr<IWindowsInspectorObserver>& observer)
{
	observers_.emplace_back(observer);
}

void WindowsInspector::Detach(const std::shared_ptr<IWindowsInspectorObserver>& observer)
{
	const size_t temp_id = ObserverInfo::GetPointerId(observer);
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[temp_id](const ObserverInfo& o)
	{
		return o.id == temp_id;
	}), observers_.end());
}

void WindowsInspector::Notify(WindowsEvents win_event, WindowsData data)
{
	// Remove any dead observers.  These are ones which have expired().
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[](const ObserverInfo& o)
	{
		return o.ptr.expired();
	}), observers_.end());

	// Notify any valid observers of events.
	std::for_each(observers_.cbegin(), observers_.cend(),
		[&](const ObserverInfo& o)
	{
		auto observer = o.ptr.lock();
		if (observer) 
		{
			observer->OnEvent(win_event, data);
		}
	});
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
	if (hwnd != GetAncestor(hwnd, GA_ROOTOWNER))
		return;
	switch (event)
	{
	case EVENT_OBJECT_CREATE:
		OutputDebugStringA("Window Created: \n");
		WindowsInspector::WindowInfo(hwnd);
		break;

	case EVENT_SYSTEM_MOVESIZEEND:
		OutputDebugStringA("Window Moved: \n");
		WindowsInspector::WindowInfo(hwnd);
		break;
	case EVENT_SYSTEM_MINIMIZESTART:
		OutputDebugStringA("Window Minimized: \n");
		WindowsInspector::WindowInfo(hwnd);
		break;
	case EVENT_SYSTEM_SWITCHEND:
		OutputDebugStringA("Window Switched: \n");
		WindowsInspector::WindowInfo(hwnd);
		break;
	case EVENT_OBJECT_DESTROY:
		OutputDebugStringA("Window Destroyed: \n");
		WindowsInspector::WindowInfo(hwnd);
		break;
	case EVENT_OBJECT_FOCUS:
		OutputDebugStringA("Focus on window: \n");
		WindowsInspector::WindowInfo(hwnd);
		break;
	default:
		break;
	}
	
}

void WindowsInspector::MessageLoop()
{
	window_hook_ = SetWinEventHook(EVENT_MIN, EVENT_MAX, hinst_, WinEventProc, 0, 0, WINEVENT_INCONTEXT | WINEVENT_SKIPOWNPROCESS);
	while (GetMessage(&message_, nullptr, 0, 0))
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
	StopAndWait();
}

void WindowsInspector::StopAndWait()
{
	if (worker_.joinable())
		worker_.join();
}