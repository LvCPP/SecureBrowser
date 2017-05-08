#include "KeyboardInspectorImpl.h"
#include <sstream>
#include <string>

static constexpr DWORD IS_PRESSED = 0x80;

HMODULE KeyboardInspectorImpl::instance = 0;
HHOOK keyboard_hook;

KeyboardInspectorImpl::KeyboardInspectorImpl()
{
}

KeySequence KeyboardInspectorImpl::current_key_seq_;
std::unordered_map<KeySequence, KeyboardInspectorImpl::KeySequenceHandler> KeyboardInspectorImpl::key_seq_to_handler_;

KeyboardInspectorImpl::~KeyboardInspectorImpl()
{
	StopAndWait();
}

void KeyboardInspectorImpl::Start()
{
	msg_loop_thread_ = std::thread(&KeyboardInspectorImpl::MessageLoop, this);

	OutputDebugStringA("Keyboard hooking started\n");
	  
}

void KeyboardInspectorImpl::Stop()
{
	PostThreadMessage(GetThreadId(msg_loop_thread_.native_handle()), WM_QUIT, 0, 0);
	OutputDebugStringA("Stop keyboard hooking.\n");
	UnhookWindowsHookEx(keyboard_hook);
	msg_loop_thread_.join();
}

void KeyboardInspectorImpl::StopAndWait()
{
	Stop();
	//msg_loop_thread_.join();
}

void KeyboardInspectorImpl::InstallKeySequenceHandler(const KeySequence& key, const KeySequenceHandler& handler)
{
	key_seq_to_handler_.emplace(key, handler);
}

void KeyboardInspectorImpl::MessageLoop()
{ 
	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardInspectorImpl::LowLevelKeyboardProc, instance, 0);

	MSG message;
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

	std::string debug;

	switch (wParam)
	{
	case WM_KEYDOWN:
		debug += "WM_KEYDOWN: ";
		break;
	case WM_KEYUP:
		debug += "WM_KEYUP: ";
		break;
	case WM_SYSKEYDOWN:
		debug += "WM_SYSKEYDOWN: ";
		break;
	case WM_SYSKEYUP:
		debug += "WM_SYSKEYUP: ";
		break;
	}

	UINT vk = kb->vkCode;
	auto it0 = key_map.find(vk);
	if (it0 != key_map.end())
		debug += key_map[vk];
	else
	{
		std::stringstream ss;
		ss << std::hex << vk << std::dec;
		std::string res(ss.str());
		debug = debug + "vk 0x" + res;
	}

	if ((kb->flags & IS_PRESSED) == 0)
	{
		debug += " just pressed \n";
		OutputDebugStringA(debug.c_str());
		current_key_seq_ += KeySequence(vk);

		auto it = key_seq_to_handler_.find(current_key_seq_);
		
		if (it != key_seq_to_handler_.end())
		{
			if (it->second)
			{
				if (!it->second(current_key_seq_))
				{
					OutputDebugStringA("IGNORED: ");
					for (UINT i = 0; i < VIRTUAL_KEY_COUNT; ++i)
						if (current_key_seq_.Bit(i))
						{
							OutputDebugStringA((key_map[i] + " ").c_str());
						}
					OutputDebugStringA("\n");
					return 1;
				}
			}
		}
	}
	else
	{
		debug += " just released \n";
		current_key_seq_ -= KeySequence(vk);
		OutputDebugStringA(debug.c_str());
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}
