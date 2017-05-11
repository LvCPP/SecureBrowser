#include "KeyboardInspectorImpl.h"

//using namespace SBKeyboardInspector;

static constexpr UINT IS_RELEASED = 0x80;

HMODULE KeyboardInspectorImpl::instance = 0;
HHOOK keyboard_hook;
MSG message;
bool KeyboardInspectorImpl::ignore_key_ = false;

KeyboardInspectorImpl::KeyboardInspectorImpl() {}

KeySequence KeyboardInspectorImpl::current_key_seq_;
std::unordered_map<KeySequence, KeyboardInspectorImpl::KeySequenceHandler> KeyboardInspectorImpl::key_seq_to_handler_;

KeyboardInspectorImpl::~KeyboardInspectorImpl()
{
	StopAndWait();
}

void KeyboardInspectorImpl::Start()
{
	msg_loop_thread_ = std::thread(&KeyboardInspectorImpl::MessageLoop, this);
	OutputDebugStringA("KEYBOARD INSPECTOR STARTED WORKING\n");
}

void KeyboardInspectorImpl::Stop()
{
	PostThreadMessage(GetThreadId(msg_loop_thread_.native_handle()), WM_QUIT, 0, 0);
	OutputDebugStringA("KEYBOARD INSPECTOR STOPPED WORKING\n");
	UnhookWindowsHookEx(keyboard_hook);
}

void KeyboardInspectorImpl::StopAndWait()
{
	Stop();
	if (msg_loop_thread_.joinable())
		msg_loop_thread_.join();
}

void KeyboardInspectorImpl::InstallKeySequenceHandler(const KeySequence& key, const KeySequenceHandler& handler)
{
	key_seq_to_handler_.emplace(key, handler);
}

bool KeyboardInspectorImpl::ChangeIgnoreFlagIfNecessary(const KeySequence& ks
	, std::unordered_map<KeySequence, KeySequenceHandler>& key_seq_to_handler)
{
	auto it = key_seq_to_handler.find(ks);
	if (it != key_seq_to_handler.end())
		if (it->second)
			return !it->second(ks);
}

void KeyboardInspectorImpl::MessageLoop()
{ 
	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardInspectorImpl::LowLevelKeyboardProc, instance, 0);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

LRESULT CALLBACK KeyboardInspectorImpl::LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HC_ACTION)
		return CallNextHookEx(NULL, code, wParam, lParam);
	
	PKBDLLHOOKSTRUCT kb = (PKBDLLHOOKSTRUCT)lParam;

	Key key(LOBYTE(kb->vkCode));
	if (!current_key_seq_.IsKeySet(key))
	{
		current_key_seq_ += key;
		std::string dbg = "key pressed: " + current_key_seq_.GetText() + "\n";
		OutputDebugStringA(dbg.c_str());
		ignore_key_ = ChangeIgnoreFlagIfNecessary(current_key_seq_, key_seq_to_handler_);
	}

	if ((kb->flags & IS_RELEASED))
	{
		current_key_seq_ -= key;
		ignore_key_ = false;
		ignore_key_ = ChangeIgnoreFlagIfNecessary(current_key_seq_, key_seq_to_handler_);
	}

	if (ignore_key_)
	{
		OutputDebugStringA("KEY IGNORED: ");
		OutputDebugStringA((current_key_seq_.GetText() + "\n").c_str());
		return 1;
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}