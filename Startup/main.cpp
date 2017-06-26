#include <Windows.h>
#include <cstdio>
#include <regex>
#include <map>

constexpr ACCESS_MASK ACCESS_RIGHTS = GENERIC_ALL;

struct RegisterData
{
	HKEY reg_key;
	LPCWSTR sub_key;
	LPCWSTR value_name;
	DWORD prev_value;
};

std::map<LPCWSTR, RegisterData> previous_reg;

bool ChangeSingleFeature(RegisterData reg_data, DWORD value)
{
	bool is_success = false;

	HKEY hkey;
	if (RegCreateKeyEx(reg_data.reg_key, reg_data.sub_key, 0, nullptr, REG_OPTION_VOLATILE, KEY_READ | KEY_WRITE | KEY_WOW64_32KEY,
		nullptr, &hkey, nullptr) == ERROR_SUCCESS)
	{
		DWORD previous_data;
		DWORD  buff;
		if (RegGetValue(hkey, nullptr, reg_data.value_name, RRF_RT_REG_DWORD, nullptr, &previous_data, &buff) == ERROR_SUCCESS)
		{
			if (previous_data != 0 && value != 0)
			{
				previous_reg[reg_data.value_name] = reg_data;
				previous_reg[reg_data.value_name].prev_value = value;
			}
		}

		if (RegSetValueEx(hkey, reg_data.value_name, 0, REG_DWORD, (PBYTE)&value, sizeof(DWORD)) == ERROR_SUCCESS)
		{
			is_success = true;
		}
		RegCloseKey(hkey);
	}

	return is_success;
}

void RestoreData()
{
	for (auto it = previous_reg.begin(); it != previous_reg.end(); ++it)
	{
		ChangeSingleFeature(it->second, it->second.prev_value);
	}
	previous_reg.clear();
}

bool ChangeAllFeatures(DWORD value)
{
	bool is_success = true;

	// Task Manager
	RegisterData data;
	data.prev_value = -1;
	data.reg_key = HKEY_CURRENT_USER;
	data.sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	data.value_name = L"DisableTaskMgr";
	if (ChangeSingleFeature(data, value) == false)
		is_success = false;

	// Change Password
	data.value_name = L"DisableChangePassword";
	if (ChangeSingleFeature(data, value) == false)
		is_success = false;

	// Lock
	data.value_name = L"DisableLockWorkstation";
	if (ChangeSingleFeature(data, value) == false)
		is_success = false;

	// Log Off
	data.sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
	data.value_name = L"NoLogOff";
	if (ChangeSingleFeature(data, value) == false)
		is_success = false;

	// Shut Down
	data.value_name = L"NoClose";
	if (ChangeSingleFeature(data, value) == false)
		is_success = false;

	// User Switching
	data.reg_key = HKEY_LOCAL_MACHINE;
	data.sub_key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System";
	data.value_name = L"HideFastUserSwitching";
	if (ChangeSingleFeature(data, value) == false)
		is_success = false;

	return is_success;
}

//Create a new desktop or open an existing one
HDESK CreateHiddenDesktop(CHAR* desktop_name)
{
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

	HDESK sb_desktop = CreateHiddenDesktop("SecureBrowser");
	HDESK original_desktop = GetThreadDesktop(GetCurrentThreadId());

	//Need to switch thread into context of new desktop to register hotkeys
	SetThreadDesktop(sb_desktop);
	ClearClipboard();
	ChangeAllFeatures(1);
	SwitchDesktop(sb_desktop);

	std::string input = path_of_executable + " " + argv[1];
	std::string path_to_browser = std::regex_replace(path_of_executable, std::regex("Startup"), "Browser");
	
	HANDLE browser = StartBrowser(path_to_browser, const_cast<char*>(input.c_str()));

	if(browser)
	{
		WaitForSingleObject(browser, INFINITE);
	}

	ChangeAllFeatures(0);
	RestoreData();

	SwitchDesktop(original_desktop);
	CloseDesktop(sb_desktop);

	ClearClipboard();

	CloseHandle(sb_desktop);
}
