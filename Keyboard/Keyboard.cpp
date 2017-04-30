#include "KeyList.h"
#include "KeyHook.h"

using namespace SecureBrowser;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// sets hook
	// if using low-level keyboard hooking WH_KEYBOARD_LL there is no need to use DLL
	HHOOK keyboard_hook;
	keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL
		, (HOOKPROC)KeyboardHooking::LowLevelKeyboardProc
		, hInstance, 0);
	//prevents from closing
	KeyboardHooking::MsgLoop();
	//unhooks
	UnhookWindowsHookEx(keyboard_hook);
	return 0;
}
