#include "FakeWindowService.h"
#include "IFakeWindowServiceObserver.h"
#include <windows.h>
#include <Wtsapi32.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <thread>

using namespace SI;

struct ObserverInfo
{
	ObserverInfo(const std::shared_ptr<IFakeWindowServiceObserver>& observer)
		: id(GetPointerId(observer))
		, ptr(observer)
	{
	};

	static size_t GetPointerId(const std::shared_ptr<IFakeWindowServiceObserver>& observer)
	{
		return reinterpret_cast<size_t>(observer.get());
	}

	size_t id;
	std::weak_ptr<IFakeWindowServiceObserver> ptr;
};

bool FakeWindowService::Start()
{
	fake_window_handle_ = ::CreateWindowA("STATIC", "fake", WS_MINIMIZE, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	if (fake_window_handle_ != NULL)
	{
		::WTSRegisterSessionNotification(fake_window_handle_, NOTIFY_FOR_ALL_SESSIONS);

		worker_ = std::thread(&FakeWindowService::StartWindowRoutine, this, fake_window_handle_);
		return true;
	}
	else
	{
		return false;
	}
}

bool FakeWindowService::Stop()
{
	bool result = DestroyWindow(fake_window_handle_);
	worker_.join();
	return result;
}

void FakeWindowService::Attach(const std::shared_ptr<IFakeWindowServiceObserver>& observer)
{
	observers_.emplace_back(observer);
}

void FakeWindowService::Detach(const std::shared_ptr<IFakeWindowServiceObserver>& observer)
{
	const size_t temp_id = ObserverInfo::GetPointerId(observer);
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[temp_id](const ObserverInfo& o)
	{
		return o.id == temp_id;
	}), observers_.end());
}

void FakeWindowService::Notify()
{
	// Remove any dead observers.  These are ones which have expired().
	observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
		[](const ObserverInfo& o)
	{
		return o.ptr.expired();
	}), observers_.end());

	// Notify any valid observers of events.
	std::for_each(observers_.cbegin(), observers_.cend(),
		[](const ObserverInfo& o)
	{
		auto observer = o.ptr.lock();
		if (observer) {
			observer->EventHappened();
		}
	});
}

bool FakeWindowService::StartWindowRoutine(HWND fake_window)
{
	MSG msg;
	BOOL result;

	while ((result = GetMessage(&msg, fake_window, 0, 0)) != 0)
	{
		if (result == -1)
		{
			//handle the error and possibly exit
			//break?
			return false;
		}
		else
		{
			if (msg.message == WM_WTSSESSION_CHANGE)
			{
#ifdef _DEBUG
				std::cout << "Event happened\n";
#endif //_DEBUG
				Notify();
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return true;
}