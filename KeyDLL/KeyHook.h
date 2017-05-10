#pragma once
#include "KeyList.h"
#include "KeyUtils.h"

namespace Keyboard
{
	// for global keyboard hooking
	class KeyboardHooking
	{
	public:
	KEY_API void StartKeyboardHooking();
	KEY_API	void StopKeyboardHooking();

	//to be run for low level hooking
	KEY_API	static LRESULT CALLBACK LowLevelKeyboardHook(int code, WPARAM wParam, LPARAM lParam);

	//the loop for getting messages
	KEY_API	static void MsgLoop();
	};

}