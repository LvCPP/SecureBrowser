#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern HINSTANCE hinst_;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hinst_ = hModule;
		break;
	default:
		break;
	}
	return TRUE;
}