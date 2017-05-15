#include <windows.h>
#include <Wtsapi32.h>
#pragma  comment(lib,"Wtsapi32.lib")
#include  "SessionInspector.h"
#define TERMINAL_SERVER_KEY                                                    \
  _T("SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\")
#define GLASS_SESSION_ID _T("GlassSessionId")


class FakeWindowService
{
public:
	FakeWindowService()
	{
		MSG msg;
		BOOL bRet;
		dummyHWND = ::CreateWindowA("STATIC", "dummy", WS_MINIMIZE, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
		::SetWindowTextA(dummyHWND, "Dummy Window!");

		::WTSRegisterSessionNotification(dummyHWND, NOTIFY_FOR_ALL_SESSIONS);

		while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
		{
			if (bRet == -1)
			{
				// handle the error and possibly exit
			}
			else
			{

				if (msg.message == WM_WTSSESSION_CHANGE)
				{
					int a = 2;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

	}
	HWND dummyHWND;
};

bool SessionInstector::IsCurrentSessionRemoteable()
{
	FakeWindowService fws;


	bool fIsRemoteable = false;

	if (GetSystemMetrics(SM_REMOTESESSION)) {
		fIsRemoteable = true;
	}
	else {
		HKEY hRegKey = NULL;
		LONG lResult;

		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TERMINAL_SERVER_KEY,
			0, // ulOptions
			KEY_READ, &hRegKey);

		if (lResult == ERROR_SUCCESS) {
			DWORD dwGlassSessionId = 0;
			DWORD cbGlassSessionId = sizeof(dwGlassSessionId);
			DWORD dwType = 0;

			lResult = RegQueryValueEx(hRegKey, GLASS_SESSION_ID,
				NULL, // lpReserved
				&dwType, (BYTE *)&dwGlassSessionId,
				&cbGlassSessionId);

			if (lResult == ERROR_SUCCESS) {
				DWORD dwCurrentSessionId = 0;

				if (ProcessIdToSessionId(GetCurrentProcessId(), &dwCurrentSessionId)) {
					fIsRemoteable = (dwCurrentSessionId != dwGlassSessionId);
				}
			}
		}

		if (hRegKey) {
			RegCloseKey(hRegKey);
		}
	}

	return fIsRemoteable;
}

SessionInstector::SessionInstector()
{

}
