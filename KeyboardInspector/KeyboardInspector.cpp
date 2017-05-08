#include "KeyboardInspector.h"
#include "KeyboardInspectorImpl.h"



struct KeySequenceIgnore
{
	constexpr bool operator()(const KeySequence&) const { return false; }
};

KeyboardInspector::KeyboardInspector()
	: impl_(std::make_unique<KeyboardInspectorImpl>())
{
}

KeyboardInspector::~KeyboardInspector()
{
}

void KeyboardInspector::Start()
{
	impl_->Start();
}

void KeyboardInspector::Stop()
{
	impl_->Stop();
}

void KeyboardInspector::InstallKeySequenceHandler(const KeySequence& key, const KeySequenceHandler& handler)
{
	impl_->InstallKeySequenceHandler(key, handler);
}

void KeyboardInspector::IgnoreKeySequence(const KeySequence& key)
{
	InstallKeySequenceHandler(key, KeySequenceIgnore());
}
