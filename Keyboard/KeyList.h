#pragma once
#include "Hooking.h"
#include <windows.h>
#include <map>

class KeyList
{
public:
	KeyList() {}

	static void SetDefaultKeyList(std::map<UINT, UINT>& key_list);
	
	void EmptyKeyListInit(std::map<UINT, UINT>& key_list);

	void AddKey(UINT key, std::map<UINT, UINT>& key_list);

	void RemoveKey(UINT key, std::map<UINT, UINT>& key_list);

	UINT GetVkCode(UINT key, std::map<UINT, UINT>& key_list);

private:
	
	static std::map <UINT, UINT> key_list;	
};



