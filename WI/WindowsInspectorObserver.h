#pragma once
#include "WindowsInspector.h"
#include "IWindowsInspectorObserver.h"
#include <vector>
#include <memory>

namespace SBWindowsInspector
{


class WindowsInspectorObserver : public IWindowsInspectorObserver
{
public:
	~WindowsInspectorObserver() = default;

	virtual void OnEvent(WindowsEvents win_event, WindowsData data) override;

private:

};

} //SBWindowsInspector