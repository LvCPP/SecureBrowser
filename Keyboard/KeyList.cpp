#include "KeyList.h"
#include <iostream>

void KeyList::SetDefaultKeyList(std::map<UINT, UINT>& key_list)
{
	if (!key_list.empty())
	{
		key_list.clear();
	}
	
	key_list[0x00] = 0x00;
	key_list[0x03] = VK_CANCEL;
	key_list[0x08] = VK_BACK;
	key_list[0x09] = VK_TAB;
	key_list[0x0C] = VK_CLEAR;
	key_list[0x0D] = VK_RETURN;
	key_list[0x10] = VK_SHIFT;
	key_list[0x11] = VK_CONTROL;
	key_list[0x12] = VK_MENU;
	key_list[0x13] = VK_PAUSE;
	key_list[0x14] = VK_CAPITAL;
	key_list[0x1B] = VK_ESCAPE;
	key_list[0x20] = VK_SPACE;
	key_list[0x21] = VK_PRIOR;
	key_list[0x22] = VK_NEXT;
	key_list[0x23] = VK_END;
	key_list[0x24] = VK_HOME;
	key_list[0x25] = VK_LEFT;
	key_list[0x26] = VK_UP;
	key_list[0x27] = VK_RIGHT;
	key_list[0x28] = VK_DOWN;
	key_list[0x29] = VK_SELECT;
	key_list[0x2A] = VK_PRINT;
	key_list[0x2B] = VK_EXECUTE;
	key_list[0x2C] = VK_SNAPSHOT;
	key_list[0x2D] = VK_INSERT;
	key_list[0x2E] = VK_DELETE;
	key_list[0x2F] = VK_HELP;
	key_list[0x30] = 0x30;
	key_list[0x31] = 0x31;
	key_list[0x32] = 0x32;
	key_list[0x33] = 0x33;
	key_list[0x34] = 0x34;
	key_list[0x35] = 0x35;
	key_list[0x36] = 0x36;
	key_list[0x37] = 0x37;
	key_list[0x38] = 0x38;
	key_list[0x39] = 0x39;
	key_list[0x41] = 0x41;
	key_list[0x42] = 0x42;
	key_list[0x43] = 0x43;
	key_list[0x44] = 0x44;
	key_list[0x45] = 0x45;
	key_list[0x46] = 0x46;
	key_list[0x47] = 0x47;
	key_list[0x48] = 0x48;
	key_list[0x49] = 0x49;
	key_list[0x4A] = 0x4A;
	key_list[0x4B] = 0x4B;
	key_list[0x4C] = 0x4C;
	key_list[0x4D] = 0x4D;
	key_list[0x4E] = 0x4E;
	key_list[0x4F] = 0x4F;
	key_list[0x50] = 0x50;
	key_list[0x51] = 0x51;
	key_list[0x52] = 0x52;
	key_list[0x53] = 0x53;
	key_list[0x54] = 0x54;
	key_list[0x55] = 0x55;
	key_list[0x56] = 0x56;
	key_list[0x57] = 0x57;
	key_list[0x58] = 0x58;
	key_list[0x59] = 0x59;
	key_list[0x5A] = 0x5A;
	key_list[0x5B] = VK_LWIN;
	key_list[0x5C] = VK_RWIN;
	key_list[0x5D] = VK_APPS;
	key_list[0x5F] = VK_SLEEP;
	key_list[0x60] = VK_NUMPAD0;
	key_list[0x61] = VK_NUMPAD1;
	key_list[0x62] = VK_NUMPAD2;
	key_list[0x63] = VK_NUMPAD3;
	key_list[0x64] = VK_NUMPAD4;
	key_list[0x65] = VK_NUMPAD5;
	key_list[0x66] = VK_NUMPAD6;
	key_list[0x67] = VK_NUMPAD7;
	key_list[0x68] = VK_NUMPAD8;
	key_list[0x69] = VK_NUMPAD9;
	key_list[0x6A] = VK_MULTIPLY;
	key_list[0x6B] = VK_ADD;
	key_list[0x6C] = VK_SEPARATOR;
	key_list[0x6D] = VK_SUBTRACT;
	key_list[0x6E] = VK_DECIMAL;
	key_list[0x6F] = VK_DIVIDE;
	key_list[0x70] = VK_F1;
	key_list[0x71] = VK_F2;
	key_list[0x72] = VK_F3;
	key_list[0x73] = VK_F4;
	key_list[0x74] = VK_F5;
	key_list[0x75] = VK_F6;
	key_list[0x76] = VK_F7;
	key_list[0x77] = VK_F8;
	key_list[0x78] = VK_F9;
	key_list[0x79] = VK_F10;
	key_list[0x7A] = VK_F11;
	key_list[0x7B] = VK_F12;
	key_list[0x90] = VK_NUMLOCK;
	key_list[0x91] = VK_SCROLL;
	key_list[0xA0] = VK_LSHIFT;
	key_list[0xA1] = VK_RSHIFT;
	key_list[0xA2] = VK_LCONTROL;
	key_list[0xA3] = VK_RCONTROL;
	key_list[0xA4] = VK_LMENU;
	key_list[0xA5] = VK_RMENU;
	key_list[0xBA] = VK_OEM_1;
	key_list[0xBC] = VK_OEM_COMMA;
	key_list[0xBD] = VK_OEM_MINUS;
	key_list[0xBE] = VK_OEM_PERIOD;
	key_list[0xBF] = VK_OEM_2;
	key_list[0xC0] = VK_OEM_3;
	key_list[0xDB] = VK_OEM_4;
	key_list[0xDC] = VK_OEM_5;
	key_list[0xDD] = VK_OEM_6;
	key_list[0xDE] = VK_OEM_7;
}

void KeyList::EmptyKeyListInit(std::map<UINT, UINT>& key_list)
{
	key_list.clear();
	key_list[0] = 0;
}

void KeyList::AddKey(UINT key, std::map<UINT, UINT>& key_list)
{
	if (key_list.count(key) == 1)
		return;
	else
		key_list.emplace(std::make_pair(key, key));
}

void KeyList::RemoveKey(UINT key, std::map<UINT, UINT>& key_list)
{
	if (key_list.count(key) == 0)
		return;
	else
		key_list.erase(key);
}

UINT KeyList::GetVkCode(UINT key, std::map<UINT, UINT>& key_list)
{
	if (key_list.count(key) == 0)
		return 0;
	else
		return key_list[key];
}


