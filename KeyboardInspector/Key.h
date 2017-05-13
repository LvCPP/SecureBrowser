#pragma once

#include "KeyboardInspectorExports.h"

#include <windows.h>
#include <unordered_map>

namespace SBKeyboardInspector
{

class KeySequence;
class Key
{
public:
	explicit Key(UINT vk_code);
	~Key() = default;

	UINT GetVirtualCode() const;
	std::string GetText() const;

	KEYBOARDINSPECTOR_API KeySequence operator+(const Key& k) const;

private:
	UINT vk_code_;
};

const static std::unordered_map <UINT, std::string> VK2TEXT =
{
	{VK_LBUTTON, "Left_Mouse"},
	{VK_RBUTTON, "Right_Mouse"},
	{VK_CANCEL, "CANCEL"},
	{VK_MBUTTON, "Middle_Mouse"},
	{VK_XBUTTON1, "X1_Mouse"},
	{VK_XBUTTON2, "X2_Mouse"},
	/*
	* 0x07 : undefined
	*/
	{VK_BACK, "BACKSPACE"},
	{VK_TAB, "TAB"},
	/*
	* 0x0A - 0x0B : reserved
	*/
	{VK_CLEAR, "CLEAR"},
	{VK_RETURN, "ENTER"},
	/*
	* 0x0E - 0x0F : undefined
	*/
	{VK_SHIFT, "SHIFT"},
	{VK_CONTROL, "CTRL"},
	{VK_MENU, "ALT"},
	{VK_PAUSE, "PAUSE"} ,
	{VK_CAPITAL, "CAPS_LOCK"},
	{VK_KANA, "IME_Kana"},
	{VK_HANGEUL, "IME_Hanguel"},
	{VK_HANGUL, "IME_Hangul"},
	/*
	* 0x16 : undefined
	*/
	{VK_JUNJA, "IME_Hunja"},
	{VK_FINAL, "IME_final"},
	{VK_HANJA, "IME_Hanja"},
	{VK_KANJI, "IME_Kanji"},
	/*
	* 0x1A : undefined
	*/
	{VK_ESCAPE, "ESC"},
	{VK_CONVERT, "IME_convert"},
	{VK_NONCONVERT, "IME_nonconvert"},
	{VK_ACCEPT, "IME_accept"},
	{VK_MODECHANGE, "IME_mode_change"},
	{VK_SPACE, "SPACEBAR"},
	{VK_PRIOR, "PAGE_UP"},
	{VK_NEXT, "PAGE_DOWN"},
	{VK_END, "END"},
	{VK_HOME, "HOME"},
	{VK_LEFT, "LEFT_ARROW"},
	{VK_UP, "UP_ARROW"},
	{VK_RIGHT, "RIGHT_ARROW"},
	{VK_DOWN, "DOWN_ARROW"},
	{VK_SELECT, "SELECT"},
	{VK_PRINT, "PRINT"},
	{VK_EXECUTE, "EXECUTE"},
	{VK_SNAPSHOT, "PRINT_SCREEN"},
	{VK_INSERT, "INS"},
	{VK_DELETE, "DEL"},
	{VK_HELP, "HELP"},

	{'0', "0"},
	{'1', "1"},
	{'2', "2"},
	{'3', "3"},
	{'4', "4"},
	{'5', "5"},
	{'6', "6"},
	{'7', "7"},
	{'8', "8"},
	{'9', "9"},
	/*
	* 0x3A - 0x40 : undefined
	*/
	{'A', "A"},
	{'B', "B"},
	{'C', "C"},
	{'D', "D"},
	{'E', "E"},
	{'F', "F"},
	{'G', "G"},
	{'H', "H"},
	{'I', "I"},
	{'J', "J"},
	{'K', "K"},
	{'L', "L"},
	{'M', "M"},
	{'N', "N"},
	{'O', "O"},
	{'P', "P"},
	{'Q', "Q"},
	{'R', "R"},
	{'S', "S"},
	{'T', "T"},
	{'U', "U"},
	{'V', "V"},
	{'W', "W"},
	{'X', "X"},
	{'Y', "Y"},
	{'Z', "Z"},

	{VK_LWIN, "Left_Win"},
	{VK_RWIN, "Right_Win"},
	{VK_APPS, "Applications"},
	/*
	* 0x5E : reserved
	*/
	{VK_SLEEP, "Sleep"},
	{VK_NUMPAD0, "NUM_0"},
	{VK_NUMPAD1, "NUM_1"},
	{VK_NUMPAD2, "NUM_2"},
	{VK_NUMPAD3, "NUM_3"},
	{VK_NUMPAD4, "NUM_4"},
	{VK_NUMPAD5, "NUM_5"},
	{VK_NUMPAD6, "NUM_6"},
	{VK_NUMPAD7, "NUM_7"},
	{VK_NUMPAD8, "NUM_8"},
	{VK_NUMPAD9, "NUM_9"},
	{VK_MULTIPLY, "NUM_*"},
	{VK_ADD, "NUM_+"},
	{VK_SEPARATOR, "NUM_,"},
	{VK_SUBTRACT, "NUM_-"},
	{VK_DECIMAL, "NUM_."},
	{VK_DIVIDE, "NUM_/"},
	{VK_F1, "F1"},
	{VK_F2, "F2"},
	{VK_F3, "F3"},
	{VK_F4, "F4"},
	{VK_F5, "F5"},
	{VK_F6, "F6"},
	{VK_F7, "F7"},
	{VK_F8, "F8"},
	{VK_F9, "F9"},
	{VK_F10, "F10"},
	{VK_F11, "F11"},
	{VK_F12, "F12"},
	{VK_F13, "F13"},
	{VK_F14, "F14"},
	{VK_F15, "F15"},
	{VK_F16, "F16"},
	{VK_F17, "F17"},
	{VK_F18, "F18"},
	{VK_F19, "F19"},
	{VK_F20, "F20"},
	{VK_F21, "F21"},
	{VK_F22, "F22"},
	{VK_F23, "F23"},
	{VK_F24, "F24"},
	/*
	* 0x88 - 0x8F : unassigned
	*/
	{VK_NUMLOCK, "NUM_LOCK"},
	{VK_SCROLL, "SCROLL_LOCK"},
	/*
	* 0x92 - 0x96 : OEM Specific
	*/
	/*
	* 0x97 - 0x9F : unassigned
	*/
	{VK_LSHIFT, "Left_SHIFT"},
	{VK_RSHIFT, "Right_SHIFT"},
	{VK_LCONTROL, "Left_CTRL"},
	{VK_RCONTROL, "Right_CTRL"},
	{VK_LMENU, "Left_ALT"},
	{VK_RMENU, "Right_ALT"},

	{VK_BROWSER_BACK, "Browser_Back"},
	{VK_BROWSER_FORWARD, "Browser_Forward"},
	{VK_BROWSER_REFRESH, "Browser_Refresh"},
	{VK_BROWSER_STOP, "Browser_Stop"},
	{VK_BROWSER_SEARCH, "Browser_Search"},
	{VK_BROWSER_FAVORITES, "Browser_Favorites"},
	{VK_BROWSER_HOME, "Browser_Home"},
	{VK_VOLUME_MUTE, "Volume_Mute"},
	{VK_VOLUME_DOWN, "Volume_Down"},
	{VK_VOLUME_UP, "Volume_Up"},
	{VK_MEDIA_NEXT_TRACK, "Next_Track"},
	{VK_MEDIA_PREV_TRACK, "Previous_Track"},
	{VK_MEDIA_STOP, "Stop_Media"},
	{VK_MEDIA_PLAY_PAUSE, "Play_Pause_Media"},
	{VK_LAUNCH_MAIL, "Start_Mail"},
	{VK_LAUNCH_MEDIA_SELECT, "Select_Media"},
	{VK_LAUNCH_APP1, "Start_Application_1"},
	{VK_LAUNCH_APP2, "Start_Application_2"},
	/*
	* 0xB8 - 0xB9 : reserved
	*/
	{VK_OEM_1, "Misc_;"},	// ';:' for US
	{VK_OEM_PLUS, "+"},		// '+' any country
	{VK_OEM_COMMA, ","},	// ',' any country
	{VK_OEM_MINUS, "-"},	// '-' any country
	{VK_OEM_PERIOD, "."},	// '.' any country
	{VK_OEM_2, "Misc_/"},	// '/?' for US
	{VK_OEM_3, "Misc_`"},	// '`~' for US
	/*
	* 0xC1 - 0xD7 : reserved
	*/
	/*
	* 0xD8 - 0xDA : unassigned
	*/
	{VK_OEM_4, "Misc_["},	//  '[{' for US
	{VK_OEM_5, "Misc_\\"},	//  '\|' for US
	{VK_OEM_6, "Misc_]"},	//  ']}' for US
	{VK_OEM_7, "Misc_\'"},	//  ''"' for US
	{VK_OEM_8, "Misc_char"},//  misc characters varied by keyboard
	/*
	* 0xE0 : reserved
	*/
	/*
	* 0xE1 : OEM specific
	*/
	{VK_OEM_102, "Misc_<>_or_\\|"},  //  "<>" or "\|" on RT 102-key kbd.
	/*
	* 0xE3 - 0xE4 : OEM specific
	*/
	{VK_PROCESSKEY, "IME_PROCESS"},
	/*
	* 0xE6 : OEM specific
	*/
	{VK_PACKET, "Packet"},
	/*
	* 0xE8 : unassigned
	*/
	/*
	* 0xE9 - 0xF5 : OEM specific
	*/
	{VK_ATTN, "Attn"},
	{VK_CRSEL, "CrSel"},
	{VK_EXSEL, "ExSel"},
	{VK_EREOF, "Erase_EOF"},
	{VK_PLAY, "Play"},
	{VK_ZOOM, "Zoom"},
	{VK_NONAME, "Reserved"},
	{VK_PA1, "PA1"},
	{VK_OEM_CLEAR, "Clear"}
	/*
	* 0xFF : reserved
	*/
};

KEYBOARDINSPECTOR_API extern const Key KEY_LCONTROL;
KEYBOARDINSPECTOR_API extern const Key KEY_RCONTROL;

KEYBOARDINSPECTOR_API extern const Key KEY_LALT;
KEYBOARDINSPECTOR_API extern const Key KEY_RALT;

KEYBOARDINSPECTOR_API extern const Key KEY_LSHIFT;
KEYBOARDINSPECTOR_API extern const Key KEY_RSHIFT;

KEYBOARDINSPECTOR_API extern const Key KEY_LWIN;
KEYBOARDINSPECTOR_API extern const Key KEY_RWIN;

KEYBOARDINSPECTOR_API extern const Key KEY_APPS;
KEYBOARDINSPECTOR_API extern const Key KEY_DEL;
KEYBOARDINSPECTOR_API extern const Key KEY_ESC;
KEYBOARDINSPECTOR_API extern const Key KEY_INS;
KEYBOARDINSPECTOR_API extern const Key KEY_PRINT;
KEYBOARDINSPECTOR_API extern const Key KEY_PRNT_SCR;
KEYBOARDINSPECTOR_API extern const Key KEY_TAB;

KEYBOARDINSPECTOR_API extern const Key KEY_C;
KEYBOARDINSPECTOR_API extern const Key KEY_F;
KEYBOARDINSPECTOR_API extern const Key KEY_G;
KEYBOARDINSPECTOR_API extern const Key KEY_I;
KEYBOARDINSPECTOR_API extern const Key KEY_N;
KEYBOARDINSPECTOR_API extern const Key KEY_O;
KEYBOARDINSPECTOR_API extern const Key KEY_P;
KEYBOARDINSPECTOR_API extern const Key KEY_R;
KEYBOARDINSPECTOR_API extern const Key KEY_S;
KEYBOARDINSPECTOR_API extern const Key KEY_V;
KEYBOARDINSPECTOR_API extern const Key KEY_X;

KEYBOARDINSPECTOR_API extern const Key KEY_F1;
KEYBOARDINSPECTOR_API extern const Key KEY_F2;
KEYBOARDINSPECTOR_API extern const Key KEY_F3;
KEYBOARDINSPECTOR_API extern const Key KEY_F4;
KEYBOARDINSPECTOR_API extern const Key KEY_F5;
KEYBOARDINSPECTOR_API extern const Key KEY_F6;
KEYBOARDINSPECTOR_API extern const Key KEY_F7;
KEYBOARDINSPECTOR_API extern const Key KEY_F8;
KEYBOARDINSPECTOR_API extern const Key KEY_F9;
KEYBOARDINSPECTOR_API extern const Key KEY_F10;
KEYBOARDINSPECTOR_API extern const Key KEY_F11;
KEYBOARDINSPECTOR_API extern const Key KEY_F12;
KEYBOARDINSPECTOR_API extern const Key KEY_F13;
KEYBOARDINSPECTOR_API extern const Key KEY_F14;
KEYBOARDINSPECTOR_API extern const Key KEY_F15;
KEYBOARDINSPECTOR_API extern const Key KEY_F16;
KEYBOARDINSPECTOR_API extern const Key KEY_F17;
KEYBOARDINSPECTOR_API extern const Key KEY_F18;
KEYBOARDINSPECTOR_API extern const Key KEY_F19;
KEYBOARDINSPECTOR_API extern const Key KEY_F20;
KEYBOARDINSPECTOR_API extern const Key KEY_F21;
KEYBOARDINSPECTOR_API extern const Key KEY_F22;
KEYBOARDINSPECTOR_API extern const Key KEY_F23;
KEYBOARDINSPECTOR_API extern const Key KEY_F24;

}  //end of namespace