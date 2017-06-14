#pragma once

#include "Key.h"

#include <string>
#include <bitset>

namespace SBKeyboardInspector
{

static constexpr size_t VIRTUAL_KEY_COUNT = 0xFF + 1;

class KeySequence 
{
public:
	KeySequence() = default;
	KEYBOARDINSPECTOR_API KeySequence(const Key& key);
	explicit KeySequence(const std::bitset<VIRTUAL_KEY_COUNT>& keys);

	bool IsKeySet(const Key& key) const;
	KEYBOARDINSPECTOR_API std::string GetText() const;
	size_t GetHash() const;

	KEYBOARDINSPECTOR_API KeySequence& operator+=(const KeySequence& ks);
	KEYBOARDINSPECTOR_API KeySequence& operator-=(const KeySequence& ks);
	KEYBOARDINSPECTOR_API KeySequence operator+(const KeySequence& ks) const;
	KEYBOARDINSPECTOR_API bool operator==(const KeySequence& ks) const;

private:
	std::bitset<VIRTUAL_KEY_COUNT> keys_;
};

} // namespace SBKeyboardInspector

namespace std
{

template<>
struct hash<SBKeyboardInspector::KeySequence>
{
	size_t operator()(const SBKeyboardInspector::KeySequence& ks) const
	{
		return ks.GetHash();
	}
};

} // namespace std






