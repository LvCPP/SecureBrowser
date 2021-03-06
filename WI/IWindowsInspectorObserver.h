#pragma once
#include "WindowsInspectorData.h"

namespace SBWindowsInspector
{
enum class WindowsEvents;

class IWindowsInspectorObserver
{
public:
	virtual  ~IWindowsInspectorObserver() = default;
	virtual void OnEvent(WindowsEvents win_event, WindowsData data) = 0;
};

} // namespace SBWindowsInspector
