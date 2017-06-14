#include "KeySequence.h"

using namespace SBKeyboardInspector;

KeySequence::KeySequence(const std::bitset<VIRTUAL_KEY_COUNT>& keys)
	: keys_(keys)
{
}

bool KeySequence::IsKeySet(const Key& key) const
{
	return keys_.test(key.GetVirtualCode());
}

KeySequence::KeySequence(const Key& key)
{
	keys_.set(key.GetVirtualCode());
}

std::string KeySequence::GetText() const
{
	std::string result;
	for (size_t i = VIRTUAL_KEY_COUNT - 1; i > 0; --i)
		if (keys_.test(i))
		{
			if (!result.empty())
				result += " + ";
			result += Key(i).GetText();
		}
	return result;
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





