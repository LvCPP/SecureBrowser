#pragma once
#include <windows.h>

class SpecialKeys
{
public:
	SpecialKeys() {}

	bool KeyIsDownNow(UINT key);
	bool KeyWasDownBefore(UINT key);
	bool KeyIsToggled(UINT key);

private:
	UINT key;
};
