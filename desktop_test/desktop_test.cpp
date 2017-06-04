#include <Windows.h>
#include <stdio.h>

const ACCESS_MASK AccessRights = DESKTOP_JOURNALRECORD | DESKTOP_JOURNALPLAYBACK | DESKTOP_CREATEWINDOW | DESKTOP_ENUMERATE | DESKTOP_WRITEOBJECTS | DESKTOP_SWITCHDESKTOP | DESKTOP_CREATEMENU | DESKTOP_HOOKCONTROL | DESKTOP_READOBJECTS;

bool changeSingleFeature(HKEY regKey, LPCWSTR subKey, DWORD value, LPCWSTR valueName)
{
	bool resultOk = false;
	HKEY hkey;
	DWORD dwDisposition;
	if (RegCreateKeyEx(regKey, subKey, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE | KEY_WOW64_32KEY, NULL, &hkey, &dwDisposition) == ERROR_SUCCESS) {
		if (RegSetValueEx(hkey, valueName, 0, REG_DWORD, (PBYTE)&value, sizeof(DWORD)) == ERROR_SUCCESS) {
			resultOk = true;
		}
		RegCloseKey(hkey);
	}
	DWORD l = GetLastError();
	return resultOk;
}

bool changeAllFeatures(DWORD value)
{
	bool resultOk = true;

	/// Task Manager
	HKEY regKey = HKEY_CURRENT_USER;
	//RegDisableReflectionKey(regKey);
	LPCWSTR subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	LPCWSTR valueName = L"DisableTaskMgr";
	if (changeSingleFeature(regKey, subKey, value, valueName) == false)
		resultOk = false;

	/// Change Password
	valueName = L"DisableChangePassword";
	if (changeSingleFeature(regKey, subKey, value, valueName) == false)
		resultOk = false;

	/// Lock
	valueName = L"DisableLockWorkstation";
	if (changeSingleFeature(regKey, subKey, value, valueName) == false)
		resultOk = false;

	/// Log Off
	subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
	valueName = L"NoLogOff";
	if (changeSingleFeature(regKey, subKey, value, valueName) == false)
		resultOk = false;

	/// Shut Down
	valueName = L"NoClose";
	if (changeSingleFeature(regKey, subKey, value, valueName) == false)
		resultOk = false;

	/// User Switching
	regKey = HKEY_LOCAL_MACHINE;
	//RegDisableReflectionKey(regKey);
	subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	valueName = L"HideFastUserSwitching";
	if (changeSingleFeature(regKey, subKey, value, valueName) == false)
		resultOk = false;

	return resultOk;
}

//Create a new desktop or open an existing one
HDESK CreateHiddenDesktop(CHAR *desktop_name)
{
	CHAR explorer_path[MAX_PATH];
	HDESK hidden_desktop = NULL, original_desktop;
	STARTUPINFOA startup_info = { 0 };
	PROCESS_INFORMATION process_info = { 0 };
	
	ExpandEnvironmentStringsA("%windir%\\explorer.exe", explorer_path, MAX_PATH - 1);

	hidden_desktop = OpenDesktopA(desktop_name, NULL, TRUE, AccessRights);
	printf("open desktop\n");
	if (!hidden_desktop)
	{
		printf("create new desktop\n");
		hidden_desktop = CreateDesktopA(desktop_name, NULL, NULL, 0, AccessRights, NULL);
		if (hidden_desktop)
		{
			original_desktop = GetThreadDesktop(GetCurrentThreadId());

			if (SetThreadDesktop(hidden_desktop))
			{
				startup_info.cb = sizeof(startup_info);
				startup_info.lpDesktop = desktop_name;

				//We need to create an explorer.exe in the context of the new desktop for start menu, etc
				//CreateProcessA(explorer_path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info);

				SetThreadDesktop(original_desktop);
			}
		}
	}
	return hidden_desktop;
}
HDESK hidden_desktop;
void StartBrowser()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.lpDesktop = L"SecureBrowser";
	ZeroMemory(&pi, sizeof(pi));
	if (!
		CreateProcess
		(
			TEXT("Browser.exe"),
			NULL, NULL, NULL, TRUE,
			NULL,
			NULL, NULL,
			&si,
			&pi
		)
		)
	{
		printf("\n\nbad: %d\n\n", GetLastError());
	}
}

void main()
{
	HDESK original_desktop;
	printf("Disable features: %d\n", changeAllFeatures(1));
	hidden_desktop = CreateHiddenDesktop("SecureBrowser");
	original_desktop = GetThreadDesktop(GetCurrentThreadId());

	printf("Entering hidden desktop\n");

	StartBrowser();

	//Need to switch thread into context of new desktop to register hotkeys
	SetThreadDesktop(hidden_desktop);
	SwitchDesktop(hidden_desktop);

	if (RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, 0x45))
	{
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				printf("Exiting hidden desktop\n");
				CloseDesktop(hidden_desktop);
				changeAllFeatures(0);
				SwitchDesktop(original_desktop);
				break;
			}
		}
	}

	CloseHandle(hidden_desktop);
	system("pause");
}