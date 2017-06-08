#pragma once
#include "windows.h"
#include "WindowsInspectorData.h"

namespace SBWindowsInspector
{
class IWindowsInspectorObserver
{
public:
	virtual  ~IWindowsInspectorObserver() = default;
	virtual void OnEvent(WindowsEvents win_event, WindowsData data) = 0;
};
}
