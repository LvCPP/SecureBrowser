#pragma once

#include "KeyboardInspectorExports.h"
#include <unordered_map>
#include <bitset>
#include <windows.h>

static constexpr std::size_t VIRTUAL_KEY_COUNT = 0xFF + 1;

class KeySequence 
{
public:
	KeySequence() = default;
	KeySequence(std::size_t keyBit);
	KeySequence(const std::bitset<VIRTUAL_KEY_COUNT>& keys);

	bool KeySequence::Bit(std::size_t keyBit);

	size_t GetHash() const;

	KEYBOARDINSPECTOR_API KeySequence& operator+=(const KeySequence& ks);
	KEYBOARDINSPECTOR_API KeySequence& operator-=(const KeySequence& ks);
	KEYBOARDINSPECTOR_API KeySequence operator+(const KeySequence& ks) const;
	KEYBOARDINSPECTOR_API bool operator==(const KeySequence& ks) const;

private:
	std::bitset<VIRTUAL_KEY_COUNT> keys_;
};

namespace std {
	template<>
	struct hash<KeySequence>
	{
		size_t operator()(const KeySequence& ks) const { return ks.GetHash(); }
	};
}

static std::unordered_map <UINT, std::string> key_map =
{
	{0x03, "CTRL-BREAK"},
	{0x08, "BACKSPACE"},
	{0x09, "TAB"},
	{0x0C, "CLEAR"},
	{0x0D, "ENTER"},
	{0x10, "SHIFT"},
	{0x11, "CTRL"},
	{0x12, "ALT"},
	{0x13, "PAUSE"},
	{0x14, "CAPSLOCK"},
	{0x1B, "ESCAPE"},
	{0x20, "SPACEBAR"},
	{0x21, "PAGEUP"},
	{0x22, "PAGEDOWN"},
	{0x23, "END"},
	{0x24, "HOME"},
	{0x25, "LEFTARROW"},
	{0x26, "UPARROW"},
	{0x27, "RIGHTARROW"},
	{0x28, "DOWNARROW"},
	{0x29, "SELECT"},
	{0x2A, "PRINT"},
	{0x2B, "EXECUTE"},
	{0x2C, "PRINTSCREEN"},
	{0x2D, "INS"},
	{0x2E, "DEL"},
	{0x2F, "HELP"},
	{0x30, "0"},
	{0x31, "1"},
	{0x32, "2"},
	{0x33, "3"},
	{0x34, "4"},
	{0x35, "5"},
	{0x36, "6"},
	{0x37, "7"},
	{0x38, "8"},
	{0x39, "9"},
	{0x41, "A"},
	{0x42, "B"},
	{0x43, "C"},
	{0x44, "D"},
	{0x45, "E"},
	{0x46, "F"},
	{0x47, "G"},
	{0x48, "H"},
	{0x49, "I"},
	{0x4A, "J"},
	{0x4B, "K"},
	{0x4C, "L"},
	{0x4D, "M"},
	{0x4E, "N"},
	{0x4F, "O"},
	{0x50, "P"},
	{0x51, "Q"},
	{0x52, "R"},
	{0x53, "S"},
	{0x54, "T"},
	{0x55, "U"},
	{0x56, "V"},
	{0x57, "W"},
	{0x58, "X"},
	{0x59, "W"},
	{0x5A, "Z"},
	{0x5B, "LWIN"},
	{0x5C, "RWIN"},
	{0x5D, "APPS"},
	{0x5F, "SLEEP"},
	{0x60, "NUM0"},
	{0x61, "NUM1"},
	{0x62, "NUM2"},
	{0x63, "NUM3"},
	{0x64, "NUM4"},
	{0x65, "NUM5"},
	{0x66, "NUM6"},
	{0x67, "NUM7"},
	{0x68, "NUM8"},
	{0x69, "NUM9"},
	{0x6A, "NUM*"},
	{0x6B, "NUM+"},
	{0x6C, "NUM\\"},
	{0x6D, "NUM-"},
	{0x6E, "NUM."},
	{0x6F, "NUM/"},
	{0x70, "F1"},
	{0x71, "F2"},
	{0x72, "F3"},
	{0x73, "F4"},
	{0x74, "F5"},
	{0x75, "F6"},
	{0x76, "F7"},
	{0x77, "F8"},
	{0x78, "F9"},
	{0x79, "F10"},
	{0x7A, "F11"},
	{0x7B, "F12"},
	{0x90, "NUMLOCK"},
	{0x91, "SCROLLLOCK"},
	{0xA0, "LSHIFT"},
	{0xA1, "RSHIFT"},
	{0xA2, "LCTRL"},
	{0xA3, "RCTRL"},
	{0xA4, "LALT"},
	{0xA5, "RALT"},
	{0xBA, ";"},
	{0xBB, "+"},
	{0xBC, ","},
	{0xBD, "-"},
	{0xBE, "."},
	{0xBF, "/"},
	{0xC0, "~"},
	{0xDB, "["},
	{0xDC, "\\"},
	{0xDD, "]"},
	{0xDE, "\'"},
	{0xFF, "Fn"}
};

KEYBOARDINSPECTOR_API extern const KeySequence KEY_LCONTROL;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_RCONTROL;

KEYBOARDINSPECTOR_API extern const KeySequence KEY_LALT;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_RALT;

KEYBOARDINSPECTOR_API extern const KeySequence KEY_LSHIFT;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_RSHIFT;

KEYBOARDINSPECTOR_API extern const KeySequence KEY_LWIN;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_RWIN;

KEYBOARDINSPECTOR_API extern const KeySequence KEY_APPS;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_DEL;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_ESC;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_INS;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_PRINT;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_PRNT_SCR; 
KEYBOARDINSPECTOR_API extern const KeySequence KEY_TAB;

KEYBOARDINSPECTOR_API extern const KeySequence KEY_C;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_G;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_N;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_O;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_P;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_R;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_S;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_V;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_X;

KEYBOARDINSPECTOR_API extern const KeySequence KEY_F1;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F2;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F3;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F4;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F5;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F6;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F7;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F8;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F9;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F10;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F11;
KEYBOARDINSPECTOR_API extern const KeySequence KEY_F12;