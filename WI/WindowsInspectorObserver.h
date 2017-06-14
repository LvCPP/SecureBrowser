#pragma once
#include "WindowsInspector.h"
#include "IWindowsInspectorObserver.h"
#include <vector>
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

class WindowsInspectorObserver : public IWindowsInspectorObserver
{
public:
	~WindowsInspectorObserver() = default;

	WINDOWSINSPECTOR_API void Attach(const std::shared_ptr<IWindowsInspectorObserver>& observer);
	WINDOWSINSPECTOR_API void Detach(const std::shared_ptr<IWindowsInspectorObserver>& observer);
	WINDOWSINSPECTOR_API void Notify(WindowsEvents win_event, WindowsData data);
	virtual void OnEvent(WindowsEvents win_event, WindowsData data) override;

private:
	std::vector<ObserverInfo> observers_;
};

} //SBWindowsInspector