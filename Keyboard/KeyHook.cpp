#include "KeyHook.h"

using namespace SecureBrowser;

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

	DWORD new_key_param = key_param->vkCode;
	// blocking of some ALT-combinations
	// blocking of all the WIN-combinations
	// blocking of all the TAB-combinations 
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_TAB)
	{
		f << "\n" << "Key combination ALT + TAB was blocked!" << "\n";
		return 1;
	}
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_ESCAPE)
	{
		f << "\n" << "Key combination ALT + ESC was blocked!" << "\n";
		return 1;
	}
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_ESCAPE
		&& shift_key_down)
	{
		f << "\n" << "Key combination ALT + SHIFT + ESC was blocked!" << "\n";
		return 1;
	}
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_TAB
		&& shift_key_down)
	{
		f << "\n" << "Key combination ALT + SHIFT + TAB was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_TAB
		&& control_key_down)
	{
		f << "\n" << "Key combination ALT + CTRL + TAB was blocked!" << "\n";
		return 1;
	} 
	if (win_key_down)
	{
		f << "\n" << "Key WIN was blocked!" << "\n";
		return 1;
	} 
	if (new_key_param == VK_PRINT)
	{
		f << "\n" << "Key Print was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN
		&& new_key_param == VK_PRINT)
	{
		f << "\n" << "Key combination Alt + Print was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN
		&& new_key_param == VK_SNAPSHOT)
	{
		f << "\n" << "Key combination Alt + PrintScreen was blocked!" << "\n";
		return 1;
	} 
	if (new_key_param == VK_SNAPSHOT)
	{
		f << "\n" << "Key Snapshot was blocked!" << "\n";
		return 1;
	} 
	if (new_key_param == VK_TAB)
	{
		f << "\n" << "Key TAB was blocked!" << "\n";
		return 1;
	}  
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_F6)
	{
		f << "\n" << "Key combination ALT + F6 was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN)
	{
		f << "\n" << "Key ALT was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_BACK)
	{
		f << "\n" << "Key combination ALT + Backspace was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_LEFT)
	{
		f << "\n" << "Key combination ALT + left arrow was blocked!" << "\n";
		return 1;
	} 
	if (key_param->flags & LLKHF_ALTDOWN && new_key_param == VK_RIGHT)
	{
		f << "\n" << "Key combination ALT + right arrow was blocked!" << "\n";
		return 1;
	}

	f.close();

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