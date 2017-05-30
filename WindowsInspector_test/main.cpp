#include <WindowsInspector.h>

int main()
{
	/*if (!installHook())
	system("pause");*/

	installHook();
	//EnumWindowsProc();
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	system("pause");
	return 0;
}