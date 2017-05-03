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

	//get the key from PKBDLLHOOKSTRUCT struct using lParam
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;

	// open "keys.txt" for writing info about keys
	std::ofstream f;
	f.open("keys.txt", std::ios::app);

	bool found_in_map = true;
	std::string name = "";
	std::map <UINT, KeyPair>::iterator it = key_map.find((*key).vkCode);
	if (it == key_map.end())
		found_in_map = false;
	
	if (found_in_map)
		name = key_map[(*key).vkCode].GetKeyName();
	else
		name = " vk " + std::to_string((*key).vkCode) + " ";
	
	if (wParam == WM_KEYDOWN)
	{
		if (GetAsyncKeyState(VK_CONTROL))
		{
			f << " CTRL " << name << " ";
			if ((*key).vkCode == 0x43 // C
				|| (*key).vkCode == 0x56 // V
				|| (*key).vkCode == 0x50 // P
				|| (*key).vkCode == 0x53 // S
				|| (*key).vkCode == 0x58 // X
				|| (*key).vkCode == VK_INSERT) // Ins
			{
				f << "\nKey combination Ctrl + " << name << " is blocked! ";
				return 1;
			}
		}
		else if (GetAsyncKeyState(VK_SHIFT))
		{
			f << " SHIFT " << name << " ";
			if ((*key).vkCode == VK_DELETE // Del
				|| (*key).vkCode == VK_F10 // F10
				|| (*key).vkCode == VK_INSERT) // Ins
			{
				f << "\nKey combination Shift + " << name << " is blocked! ";
				return 1;
			}
		}

		else if (GetAsyncKeyState(VK_LWIN) || GetAsyncKeyState(VK_RWIN))
		{
			f << " WIN " << name << " ";
			f << "\nWin key is blocked! \n";
			return 1;
		}
		else if ((*key).vkCode == VK_PRINT
			|| (*key).vkCode == VK_SNAPSHOT
			|| (*key).vkCode == VK_APPS)
		{
			f << " " << name << " ";
			f << "\nKey " << name << " is blocked! ";
			return 1;
		}
		else if (((*key).vkCode >= 0x70 // F1
			&& ((*key).vkCode <= 0x7B))) // F12
			f << name << " ";
	}

	else if (wParam == WM_SYSKEYDOWN)
	{
		if (GetAsyncKeyState(VK_MENU))
		{
			f << " ALT " << name << " ";
			if ((*key).vkCode == VK_TAB
				|| (*key).vkCode == VK_PRINT
				|| (*key).vkCode == VK_SNAPSHOT
				|| (*key).vkCode == VK_F6
				|| (*key).vkCode == VK_ESCAPE)
			{
				f << "\nKey combination Alt + " << name << " is blocked! \n";
				return 1;
			}
		}
		else
			f << " " << name << " ";
	}
	
	f.close();
	return CallNextHookEx(NULL, code, wParam, lParam);
}