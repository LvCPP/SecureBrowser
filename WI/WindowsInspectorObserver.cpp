#include "WindowsInspectorObserver.h"
#include <memory>
#include <algorithm>

using namespace SBWindowsInspector;

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

void WindowsInspectorObserver::Attach(const std::shared_ptr<IWindowsInspectorObserver>& observer)
{
	observers_.emplace_back(observer);
}

void WindowsInspectorObserver::Detach(const std::shared_ptr<IWindowsInspectorObserver>& observer)
{
	const size_t temp_id = ObserverInfo::GetPointerId(observer);
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[temp_id](const ObserverInfo& o)
	{
		return o.id == temp_id;
	}), observers_.end());
}

void WindowsInspectorObserver::Notify(char wnd_title_, DWORD processID, wchar_t processname)
{
	// Remove any dead observers.  These are ones which have expired().
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[](const ObserverInfo& o)
	{
		return o.ptr.expired();
	}), observers_.end());

	// Notify any valid observers of events.
	std::for_each(observers_.cbegin(), observers_.cend(),
		[wnd_title_, processID, processname](const ObserverInfo& o)
	{
		auto observer = o.ptr.lock();
		if (observer) {
			observer->OnWindowChanged(wnd_title_, processID,  processname);
		}
	});
}
