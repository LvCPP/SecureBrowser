#include "WindowsInspectorObserver.h"
#include <memory>
#include <algorithm>

using namespace SBWindowsInspector;

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

void WindowsInspectorObserver::Notify(WindowsEvents win_event, WindowsData data)
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
		if (observer) {
			observer->OnEvent(win_event, data);
		}
	});
}

void WindowsInspectorObserver::OnEvent(WindowsEvents win_event, WindowsData data)
{
	std::cout << "check" << std::endl;
}
