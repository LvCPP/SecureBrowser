#pragma once

#include "KeySequence.h"

#include <memory>
#include <functional>

namespace SBKeyboardInspector
{

class KeyboardInspector
{
public:
	using KeySequenceHandler = std::function<bool(const KeySequence&)>;

	KEYBOARDINSPECTOR_API KeyboardInspector();
	KEYBOARDINSPECTOR_API ~KeyboardInspector();

	KEYBOARDINSPECTOR_API void Start();
	KEYBOARDINSPECTOR_API void Stop();
	
	KEYBOARDINSPECTOR_API void InstallKeySequenceHandler(const KeySequence& key, const KeySequenceHandler& handler);
	KEYBOARDINSPECTOR_API void IgnoreKeySequence(const KeySequence& key);

private:
	std::unique_ptr<class KeyboardInspectorImpl> impl_;
};


} // namespace SBKeyboardInspector





