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

class FakeWindowService
{
public:
	bool Start();
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