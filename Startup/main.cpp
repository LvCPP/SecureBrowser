#include <Windows.h>
#include <cstdio>
#include <regex>

constexpr ACCESS_MASK ACCESS_RIGHTS = GENERIC_ALL;

bool ChangeSingleFeature(HKEY reg_key, LPCWSTR sub_key, DWORD value, LPCWSTR value_name)
{
	bool is_success = false;

	HKEY hkey;
	if (RegCreateKeyEx(reg_key, sub_key, 0, nullptr, REG_OPTION_VOLATILE, KEY_WRITE | KEY_WOW64_32KEY,
		nullptr, &hkey, nullptr) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(hkey, value_name, 0, REG_DWORD, (PBYTE)&value, sizeof(DWORD)) == ERROR_SUCCESS)
		{
			is_success = true;
		}
		RegCloseKey(hkey);
	}

	return is_success;
}

bool ChangeAllFeatures(DWORD value)
{
	bool is_success = true;

	// Task Manager
	HKEY reg_key = HKEY_CURRENT_USER;
	LPCWSTR sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	LPCWSTR value_name = L"DisableTaskMgr";
	if (ChangeSingleFeature(reg_key, sub_key, value, value_name) == false)
		is_success = false;

	// Change Password
	value_name = L"DisableChangePassword";
	if (ChangeSingleFeature(reg_key, sub_key, value, value_name) == false)
		is_success = false;

	// Lock
	value_name = L"DisableLockWorkstation";
	if (ChangeSingleFeature(reg_key, sub_key, value, value_name) == false)
		is_success = false;

	// Log Off
	sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
	value_name = L"NoLogOff";
	if (ChangeSingleFeature(reg_key, sub_key, value, value_name) == false)
		is_success = false;

	// Shut Down
	value_name = L"NoClose";
	if (ChangeSingleFeature(reg_key, sub_key, value, value_name) == false)
		is_success = false;

	// User Switching
	reg_key = HKEY_LOCAL_MACHINE;
	sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	value_name = L"HideFastUserSwitching";
	if (ChangeSingleFeature(reg_key, sub_key, value, value_name) == false)
		is_success = false;

	return is_success;
}

//Create a new desktop or open an existing one
HDESK CreateHiddenDesktop(CHAR* desktop_name)
{
	CHAR explorer_path[MAX_PATH];
	
	ExpandEnvironmentStringsA("%windir%\\explorer.exe", explorer_path, MAX_PATH - 1);

	HDESK hidden_desktop = OpenDesktopA(desktop_name, NULL, TRUE, ACCESS_RIGHTS);
	if (!hidden_desktop)
	{
		hidden_desktop = CreateDesktopA(desktop_name, nullptr, nullptr, 0, ACCESS_RIGHTS, nullptr);
	}
	return hidden_desktop;
}

HANDLE StartBrowser(std::string path_to_browser = "Browser.exe", LPSTR browser_argv = nullptr)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);
	si.lpDesktop = "SecureBrowser";

	if (!CreateProcessA(const_cast<char*>(path_to_browser.c_str()), browser_argv, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi))
	{
		return nullptr;
	}
	return pi.hProcess;
}

void ClearClipboard()
{
	if (OpenClipboard(nullptr))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}

void ExitAlertDialog(LPCTSTR message)
{
	MessageBox(nullptr, message, L"Error", MB_ICONERROR);
}

void main(int argc, char** argv)
{
	if (argc != 2)
	{
		ExitAlertDialog(L"You can start Secure Browser only via invite link!");
		return;
	}

	std::string path_of_executable = argv[0];
	if (path_of_executable.find(" ") != std::string::npos)
	{
		ExitAlertDialog(L"Make sure your path doesn't include whitespaces");
		return;
	}

	ChangeAllFeatures(1);
	
	HDESK sb_desktop = CreateHiddenDesktop("SecureBrowser");
	HDESK original_desktop = GetThreadDesktop(GetCurrentThreadId());

	//Need to switch thread into context of new desktop to register hotkeys
	SetThreadDesktop(sb_desktop);
	ClearClipboard();
	SwitchDesktop(sb_desktop);

	std::string input = path_of_executable + " " + argv[1];
	std::string path_to_browser = std::regex_replace(path_of_executable, std::regex("Startup"), "Browser");



	HANDLE browser = StartBrowser(path_to_browser, const_cast<char*>(input.c_str()));

	if(browser)
	{
		WaitForSingleObject(browser, INFINITE);
	}

	CloseDesktop(sb_desktop);

	ChangeAllFeatures(0);
	ClearClipboard();
	SwitchDesktop(original_desktop);

	CloseHandle(sb_desktop);
}