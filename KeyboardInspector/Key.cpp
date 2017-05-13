#include "Key.h"
#include "KeySequence.h"

#include <string>

using namespace SBKeyboardInspector;

Key::Key(UINT vk_code) 
	: vk_code_(vk_code) 
{
}

UINT Key::GetVirtualCode() const
{
	return vk_code_;
}

std::string Key::GetText() const
{
	auto it = VK2TEXT.find(Key::GetVirtualCode());
	if (it != VK2TEXT.end())
		return it->second;
	else
		return "VK (" + std::to_string(Key::GetVirtualCode()) + ") ";
}

KeySequence Key::operator+(const Key& k) const
{
	return KeySequence(*this) + k;
}

namespace SBKeyboardInspector
{

	const Key KEY_LCONTROL = Key(VK_LCONTROL);
	const Key KEY_RCONTROL = Key(VK_RCONTROL);

	const Key KEY_LALT = Key(VK_LMENU);
	const Key KEY_RALT = Key(VK_RMENU);

	const Key KEY_LSHIFT = Key(VK_LSHIFT);
	const Key KEY_RSHIFT = Key(VK_RSHIFT);

	const Key KEY_LWIN = Key(VK_LWIN);
	const Key KEY_RWIN = Key(VK_RWIN);

	const Key KEY_APPS = Key(VK_APPS);
	const Key KEY_DEL = Key(VK_DELETE);
	const Key KEY_ESC = Key(VK_ESCAPE);
	const Key KEY_INS = Key(VK_INSERT);
	const Key KEY_PRINT = Key(VK_PRINT);
	const Key KEY_PRNT_SCR = Key(VK_SNAPSHOT);
	const Key KEY_TAB = Key(VK_TAB);

	const Key KEY_C = Key('C');
	const Key KEY_F = Key('F');
	const Key KEY_G = Key('G');
	const Key KEY_I = Key('I');
	const Key KEY_N = Key('N');
	const Key KEY_O = Key('O');
	const Key KEY_P = Key('P');
	const Key KEY_R = Key('R');
	const Key KEY_S = Key('S');
	const Key KEY_V = Key('V');
	const Key KEY_X = Key('X');

	const Key KEY_F1 = Key(VK_F1);
	const Key KEY_F2 = Key(VK_F2);
	const Key KEY_F3 = Key(VK_F3);
	const Key KEY_F4 = Key(VK_F4);
	const Key KEY_F5 = Key(VK_F5);
	const Key KEY_F6 = Key(VK_F6);
	const Key KEY_F7 = Key(VK_F7);
	const Key KEY_F8 = Key(VK_F8);
	const Key KEY_F9 = Key(VK_F9);
	const Key KEY_F10 = Key(VK_F10);
	const Key KEY_F11 = Key(VK_F11);
	const Key KEY_F12 = Key(VK_F12);
	const Key KEY_F13 = Key(VK_F13);
	const Key KEY_F14 = Key(VK_F14);
	const Key KEY_F15 = Key(VK_F15);
	const Key KEY_F16 = Key(VK_F16);
	const Key KEY_F17 = Key(VK_F17);
	const Key KEY_F18 = Key(VK_F18);
	const Key KEY_F19 = Key(VK_F19);
	const Key KEY_F20 = Key(VK_F20);
	const Key KEY_F21 = Key(VK_F21);
	const Key KEY_F22 = Key(VK_F22);
	const Key KEY_F23 = Key(VK_F23);
	const Key KEY_F24 = Key(VK_F24);

}