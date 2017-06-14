#pragma once
#include "WindowsInspectorData.h"
#include "WindowsInspector.h"
#include "windows.h"

namespace SBWindowsInspector
{

class IWindowsInspectorObserver
{
public:
	virtual  ~IWindowsInspectorObserver() = default;
	virtual void OnEvent(WindowsEvents win_event, WindowsData data) = 0;
};

} //SBWindowsInspector
