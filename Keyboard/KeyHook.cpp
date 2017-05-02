#include "KeyHook.h"

using namespace Keyboard;

void KeyboardHooking::StartKeyboardHooking()
{
	// TBD
}

void KeyboardHooking::StopKeyboardHooking()
{
	// TBD
}

void KeyboardHooking::MsgLoop()
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

LRESULT CALLBACK KeyboardHooking::LowLevelKeyboardHook(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0 || code != HC_ACTION)
		// accept the next message
		return CallNextHookEx(NULL, code, wParam, lParam);

	typedef struct tagKBDLLHOOKSTRUCT
	{
		DWORD     vkCode;
		DWORD     scanCode;
		DWORD     flags;
		DWORD     time;
		ULONG_PTR dwExtraInfo;
	} KBDLLHOOKSTRUCT;

	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;

	std::string key_name = "";

	std::ofstream f;
	f.open("keys.txt", std::ios::app);

	BOOL control_key_down
		= ((GetAsyncKeyState(VK_CONTROL) < 0)
			|| (GetAsyncKeyState(VK_LCONTROL) < 0)
			|| (GetAsyncKeyState(VK_RCONTROL) < 0));

	//checks if shift key is pressed
	BOOL shift_key_down
		= ((GetAsyncKeyState(VK_SHIFT) < 0)
			|| (GetAsyncKeyState(VK_LSHIFT) < 0)
			|| (GetAsyncKeyState(VK_RSHIFT) < 0));

	//checks if win key is pressed
	BOOL win_key_down
		= ((GetAsyncKeyState(VK_LWIN) < 0)
			|| (GetAsyncKeyState(VK_RWIN) < 0));

	BOOL is_special = control_key_down || shift_key_down || win_key_down;

	DWORD new_key_flags = (*key).flags;
	if (new_key_flags & LLKHF_ALTDOWN
		&& (*key).vkCode >= 0x03
		&& (*key).vkCode <= 0xDE
		&& (*key).vkCode != VK_SHIFT
		&& (*key).vkCode != VK_LSHIFT
		&& (*key).vkCode != VK_RSHIFT
		&& (*key).vkCode != VK_MENU
		&& (*key).vkCode != VK_LMENU
		&& (*key).vkCode != VK_RMENU)
	{
		f << "\n" << "ALT key + vc " << (*key).vkCode << " was blocked!\n";
		return 1;
	}

	if (GetAsyncKeyState(VK_LWIN) < 0 || GetAsyncKeyState(VK_RWIN) < 0 )
	{
		f << "\n" << "Key WIN was blocked!\n";
		return 1;
	}

	if (GetAsyncKeyState(VK_TAB) < 0)
	{
		f << "\n" << "Key TAB was blocked!\n";
		return 1;
	}

	// check if the key is in the list of key combinations to be blocked
	for (UINT i = 0; i < block_list.size(); ++i)
		if (block_list[i].control_key_down == (CtrlEnum)control_key_down
			&& block_list[i].shift_key_down == (ShiftEnum)shift_key_down
			&& block_list[i].key_code == (*key).vkCode)
		{
			f << "\n";
			if (block_list[i].control_key_down == CTRL_DOWN)
				f << "CTRL";
			if (block_list[i].shift_key_down == SHIFT_DOWN)
				f << "SHIFT";
			f << " + vc " << (*key).vkCode << " was blocked!\n";
			return 1; // block the keys and key combinations
		}

	if ((*key).vkCode == VK_PRINT)
	{
		f << "\nKey PRINT was blocked!" << "\n";
		return 1;
	}
	if ((*key).vkCode == VK_SNAPSHOT)
	{
		f << "\nKey SNAPSHOT was blocked!" << "\n";
		return 1;
	}

	// if not-alt key pressed
	if (wParam == WM_KEYDOWN)
	{
		if (!is_special)
		{
			if ((*key).vkCode == VK_PRINT || (*key).vkCode == VK_SNAPSHOT
				|| (*key).vkCode == VK_APPS || (*key).vkCode == VK_LMENU
				|| (*key).vkCode >= 0x70 && (*key).vkCode <= 0x7B)
				key_name = key_name + " " + key_map[(*key).vkCode].GetKeyName();
		}
		else
		{
			if (control_key_down) key_name = "CTRL " + key_name;
			if (shift_key_down) key_name = "SHIFT " + key_name;
			if (win_key_down) key_name = "WIN " + key_name;
			key_name = key_name + " " + key_map[(*key).vkCode].GetKeyName();
		}
	}
	if (key_name != "")
		f << key_name << " ";
	f.close();
	return CallNextHookEx(NULL, code, wParam, lParam);
}