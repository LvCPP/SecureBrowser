#include "WindowsInspectorData.h"
#include <Windows.h>
#include <string>

using namespace SBWindowsInspector;

WindowsData::WindowsData(HWND hwnd)
	: hwnd_(hwnd)
{
}

UINT WindowsData::GetEventCode() const
{
	return event_code_;
}

char* WindowsData::GetTitle()
{
	return wnd_title_;
}

char* WindowsData::GetProcessName()
{
	return process_name_;
}

DWORD WindowsData::GetProcessId()
{
	return processid_;
}

std::string WindowsData::GetText() const
{
	auto it = Events.find(WindowsData::GetEventCode());
	if (it != Events.end())
		return it->second;
	else
		return "Event (" + std::to_string(WindowsData::GetEventCode()) + ") ";
}

void WindowsData::SetTitle(char* wnd_title)
{ 
	wnd_title_ = new char[strlen(wnd_title)];
	strcpy(wnd_title_, wnd_title);
}

void WindowsData::SetProcessName(char* process_name)
{ 
	process_name_ = new char[strlen(process_name)];
	strcpy(process_name_, process_name); 
}

void WindowsData::SetProcessId(DWORD processid)
{ 
	processid_ = processid; 
}

void WindowsData::SetHwnd(HWND hwnd)
{
	hwnd_ = hwnd;
}