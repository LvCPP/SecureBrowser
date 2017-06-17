#include "KeyboardInspectorImpl.h"

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace SBKeyboardInspector;

extern HMODULE h_instance;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		KeyboardInspectorImpl::instance = hModule;
		break;
	default:
		break;
	}
	return TRUE;
}

