#include "WindowsInspectorObserver.h"

using namespace SBWindowsInspector;


void WindowsInspectorObserver::OnEvent(WindowsEvents win_event, WindowsData data)
{
	std::cout << "On Event" << std::endl;
}