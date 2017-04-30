#pragma once
#include "Key.h"
#include <windows.h>
#include <fstream>

// for bitwise operations
const int SHIFT_BITS = sizeof(SHORT) * 8 - 1;

// for global keyboard hooking
class KeyboardHooking
{
public:
	void StartKeyboardHooking();
	void StopKeyboardHooking();

	//to be run for low level hooking
	static LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam);

	//the loop for getting messages
	static void MsgLoop();
};