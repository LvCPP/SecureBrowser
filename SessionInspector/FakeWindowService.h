#pragma once
#include "IFakeWindowServiceObserver.h"
#include <windows.h>
#include <Wtsapi32.h>
#include <vector>
#include <memory>
#include <thread>

struct ObserverInfo;

namespace SI
{


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

class FakeWindowService
{
public:
	void Start();
	bool Stop();
	void Attach(const std::shared_ptr<IFakeWindowServiceObserver>& observer);
	void Detach(const std::shared_ptr<IFakeWindowServiceObserver>& observer);

private:
	void Notify();
	bool StartWindowRoutine(HWND fake_window);

	std::vector<ObserverInfo> observers_;
	HWND fake_window_handle_;
	std::thread worker_;
};

}//namespace SI