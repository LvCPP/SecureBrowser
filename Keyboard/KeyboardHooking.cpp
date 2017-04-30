#include "KeyboardHooking.h"

void KeyboardHooking::StartKeyboardHooking()
{
	// TBD
}

void KeyboardHooking::StopKeyboardHooking()
{
	// TBD
}

void KeyboardHooking::MsgLoop()
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

LRESULT CALLBACK KeyboardHooking::LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0 || code != HC_ACTION)
		// accept the next message
		return CallNextHookEx(NULL, code, wParam, lParam);
	
	//get the key from PKBDLLHOOKSTRUCT struct using lParam
	PKBDLLHOOKSTRUCT key_param = (PKBDLLHOOKSTRUCT)lParam;
	
	//checks if ctrl key is pressed
	bool control_key_down
		= ((GetAsyncKeyState(VK_CONTROL) >> SHIFT_BITS)
			|| (GetAsyncKeyState(VK_LCONTROL) >> SHIFT_BITS)
			|| (GetAsyncKeyState(VK_RCONTROL) >> SHIFT_BITS));

	//checks if shift key is pressed
	bool shift_key_down
		= ((GetAsyncKeyState(VK_SHIFT) >> SHIFT_BITS)
			|| (GetAsyncKeyState(VK_LSHIFT) >> SHIFT_BITS)
			|| (GetAsyncKeyState(VK_RSHIFT) >> SHIFT_BITS));

	//checks if win key is pressed
	bool win_key_down
		= ((GetAsyncKeyState(VK_LWIN) >> SHIFT_BITS)
			|| (GetAsyncKeyState(VK_RWIN) >> SHIFT_BITS));

	// open "keys.txt" for writing info about keys
	std::ofstream f;
	f.open("keys.txt", std::ios::app);

	// for key combinations with ALT
	if (wParam == WM_SYSKEYDOWN)
	{
		f << "[Alt " << key_map[key_param->vkCode].GetKeyName() << " ] ";
	}

	f.close();

	// blocking of some ALT-combinations
	// blocking of all the WIN-combinations
	// blocking of all the TAB-combinations 
	if ((key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_TAB) // ALT + TAB
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_ESCAPE) // ALT + ESC
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_ESCAPE
			&& shift_key_down) // ALT + SHIFT + ESC
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_TAB
			&& shift_key_down) // ALT + SHIFT + TAB 
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_TAB
			&& control_key_down) // ALT + CTRL + TAB 
		|| (win_key_down) // WIN
		|| (key_param->vkCode == VK_PRINT) // Print
		|| (key_param->flags & LLKHF_ALTDOWN
			&& key_param->vkCode == VK_PRINT) // Alt + Print
		|| (key_param->flags & LLKHF_ALTDOWN
			&& key_param->vkCode == VK_SNAPSHOT) // Alt + PrintScreen
		|| (key_param->vkCode == VK_SNAPSHOT) // Snapshot
		|| (key_param->vkCode == VK_TAB) // TAB 
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_F6) // ALT + F6
		|| (key_param->flags & LLKHF_ALTDOWN) // ALT
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_BACK) // ALT + Backspace
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_LEFT) // ALT + left arrow
		|| (key_param->flags & LLKHF_ALTDOWN && key_param->vkCode == VK_RIGHT)) // ALT + right arrow
		// block the keys and key combinations
		return 1;

	std::string key_name = "";

	// if not-alt key pressed
	if (wParam == WM_KEYDOWN)
	{
		// create a KeyCombo object
		KeyCombo key_combo((CtrlEnum)control_key_down
			, (ShiftEnum)shift_key_down
			, (WinEnum)win_key_down
			, key_param->vkCode);

		std::map <UINT, KeyPair>::iterator it = key_map.find(key_param->vkCode);
		
		// if the key is in the list of the keys to be inspected
		if (it == key_map.end()) // not found in the list
			key_name += "virtual key code: " + std::to_string(key_param->vkCode) + " ";
		else  // found un the list
			key_name += key_map[key_param->vkCode].GetKeyName() + " ";

		// print info about key or key combination
		key_combo.Print(key_name);

		// check if the key is in the list of keys to be blocked
		for (UINT i = 0; i < block_list.size(); ++i)
		{
			if (block_list[i].control_key_down == (CtrlEnum)control_key_down
				&& block_list[i].shift_key_down == (ShiftEnum)shift_key_down
				&& block_list[i].key_code == key_param->vkCode)
				return 1; // block the keys and key combinations
		}
	}
	// call the next message
	return CallNextHookEx(NULL, code, wParam, lParam);
}