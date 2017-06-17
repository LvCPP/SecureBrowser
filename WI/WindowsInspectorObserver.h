#pragma once
#include "WindowsInspector.h"
#include "IWindowsInspectorObserver.h"

namespace SBWindowsInspector
{


class WindowsInspectorObserver : public IWindowsInspectorObserver
{
public:
	~WindowsInspectorObserver() = default;

	void OnEvent(WindowsEvents win_event, WindowsData data) override;
};

} // namespace SBWindowsInspector
