#include <WindowsInspector.h>

using namespace SBWindowsInspector;

int main()
{
	WindowsInspector wi;
	wi.StartWindowsInspector();
	Sleep(150000);
	wi.StopWindowsInspector();


	system("pause");
	return 0;
}