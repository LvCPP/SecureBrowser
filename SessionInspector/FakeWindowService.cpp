#include "FakeWindowService.h"
#include <windows.h>
#include <Wtsapi32.h>
#include <iostream>

using namespace SI;

void FakeWindowService::MakeFakeWindow()
{
	MSG msg;
	BOOL result;
	HWND fake_hwnd = ::CreateWindowA("STATIC", "fake", WS_MINIMIZE, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	::SetWindowTextA(fake_hwnd, "Dummy Window!");

	::WTSRegisterSessionNotification(fake_hwnd, NOTIFY_FOR_ALL_SESSIONS);

	while ((result = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (result == -1)
		{
			//handle the error and possibly exit
			//break?
		}
		else
		{
			if (msg.message == WM_WTSSESSION_CHANGE)
			{
#ifdef _DEBUG
				std::cout << "Event happened\n";
#endif //_DEBUG
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
