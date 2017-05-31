#pragma once
#include "WindowsInspector.h"
#include "IWindowsInspectorObserver.h"
#include <vector>

struct ObserverInfo;

namespace SBWindowsInspector
{

class WindowsInspectorObserver
{
public:
	~WindowsInspectorObserver() = default;

	void Attach(const std::shared_ptr<IWindowsInspectorObserver>& observer);
	void Detach(const std::shared_ptr<IWindowsInspectorObserver>& observer);
private:
	void Notify(char wnd_title, DWORD processID, wchar_t processname);

	char wnd_title;
	DWORD processID;
	wchar_t processname;

	std::vector<ObserverInfo> observers_;

};


}
