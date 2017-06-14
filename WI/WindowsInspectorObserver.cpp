#include "WindowsInspectorObserver.h"
#include <memory>
#include <algorithm>

using namespace SBWindowsInspector;


void WindowsInspectorObserver::OnEvent(WindowsEvents win_event, WindowsData data)
{
	std::cout << "check" << std::endl;
}
