#pragma once
#include "IWindowsInspectorObserver.h"
#include "WindowsInspectorUtils.h"
#include "WindowsInspectorData.h"
#include <Logger.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <memory>


namespace SBWindowsInspector
{

struct ObserverInfo
{
	ObserverInfo(const std::shared_ptr<IWindowsInspectorObserver>& observer)
		: id(GetPointerId(observer))
		, ptr(observer)
	{
	};


	static size_t GetPointerId(const std::shared_ptr<IWindowsInspectorObserver>& observer)
	{
		return reinterpret_cast<size_t>(observer.get());
	}

	size_t id;
	std::weak_ptr<IWindowsInspectorObserver> ptr;
};


enum class WindowsEvents
{
	WindowCreated,
	WindowMoved,
	WindowMinimized,
	WindowSwitched,
	WindowDestroyed,
	WindowFocusChanged
};


class WindowsInspector 
{
public:
	WINDOWSINSPECTOR_API void StartWindowsInspector();
	WINDOWSINSPECTOR_API void StopWindowsInspector();
	void StopAndWait();

	static WindowsData WindowInfo(HWND hwnd);

	WINDOWSINSPECTOR_API void Attach(const std::shared_ptr<IWindowsInspectorObserver>& observer);
	WINDOWSINSPECTOR_API void Detach(const std::shared_ptr<IWindowsInspectorObserver>& observer);
	WINDOWSINSPECTOR_API void Notify(WindowsEvents win_event, WindowsData data);

protected:
	void MessageLoop();

private:
	std::thread worker_;
	std::vector<ObserverInfo> observers_;

};

} // namespace SBWindowsInspector