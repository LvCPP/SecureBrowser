#include "KeySequence.h"

KeySequence::KeySequence(std::size_t keyBit)
{
	keys_.set(keyBit);
}

KeySequence::KeySequence(const std::bitset<VIRTUAL_KEY_COUNT>& keys)
	: keys_(keys)
{

}

bool KeySequence::Bit(std::size_t keyBit)
{
	return (keys_.test(keyBit)) ? true : false;
}

size_t KeySequence::GetHash() const
{
	return keys_.hash();
}

KeySequence& KeySequence::operator+=(const KeySequence& ks)
{
	keys_ |= ks.keys_;
	return *this;
}

KeySequence& KeySequence::operator-=(const KeySequence& ks)
{
	keys_ &= ~ks.keys_;
	return *this;
}

KeySequence KeySequence::operator+(const KeySequence& ks) const
{
	return KeySequence(keys_ | ks.keys_);
}

bool KeySequence::operator==(const KeySequence& ks) const
{
	return keys_ == ks.keys_;
}

const KeySequence KEY_LCONTROL = KeySequence(VK_LCONTROL);
const KeySequence KEY_RCONTROL = KeySequence(VK_RCONTROL);

const KeySequence KEY_LALT = KeySequence(VK_LMENU);
const KeySequence KEY_RALT = KeySequence(VK_RMENU);

const KeySequence KEY_LSHIFT = KeySequence(VK_LSHIFT);
const KeySequence KEY_RSHIFT = KeySequence(VK_RSHIFT);

const KeySequence KEY_LWIN = KeySequence(VK_LWIN);
const KeySequence KEY_RWIN = KeySequence(VK_RWIN);

const KeySequence KEY_APPS = KeySequence(VK_APPS);
const KeySequence KEY_DEL = KeySequence(VK_DELETE);
const KeySequence KEY_ESC = KeySequence(VK_ESCAPE);
const KeySequence KEY_INS = KeySequence(VK_INSERT);
const KeySequence KEY_PRINT = KeySequence(VK_PRINT);
const KeySequence KEY_PRNT_SCR = KeySequence(VK_SNAPSHOT); 
const KeySequence KEY_TAB = KeySequence(VK_TAB);

const KeySequence KEY_C = KeySequence(0x43);
const KeySequence KEY_F = KeySequence(0x46);
const KeySequence KEY_G = KeySequence(0x47);
const KeySequence KEY_I = KeySequence(0x49);
const KeySequence KEY_N = KeySequence(0x4E);
const KeySequence KEY_O = KeySequence(0x4F);
const KeySequence KEY_P = KeySequence(0x50);
const KeySequence KEY_R = KeySequence(0x52);
const KeySequence KEY_S = KeySequence(0x53);
const KeySequence KEY_V = KeySequence(0x56);
const KeySequence KEY_X = KeySequence(0x58);

const KeySequence KEY_F1 = KeySequence(VK_F1);
const KeySequence KEY_F2 = KeySequence(VK_F2);
const KeySequence KEY_F3 = KeySequence(VK_F3);
const KeySequence KEY_F4 = KeySequence(VK_F4);
const KeySequence KEY_F5 = KeySequence(VK_F5);
const KeySequence KEY_F6 = KeySequence(VK_F6);
const KeySequence KEY_F7 = KeySequence(VK_F7);
const KeySequence KEY_F8 = KeySequence(VK_F8);
const KeySequence KEY_F9 = KeySequence(VK_F9);
const KeySequence KEY_F10 = KeySequence(VK_F10);
const KeySequence KEY_F11 = KeySequence(VK_F11);
const KeySequence KEY_F12 = KeySequence(VK_F12);



