#pragma once
#include <windows.h>
#include <map>
#include <iostream>
#include <fstream>

#define SCAN_CODE_SHIFT 16;

class KeyPair
{
public:
	KeyPair() {}
	KeyPair (UINT vk_code, std::string key_name) : vk(vk_code), name(key_name) {}
	std::string GetKeyName();
private:
	UINT vk;
    std::string name;
};

static std::map <UINT, KeyPair> key;

void InitKeyMap(std::map <UINT, KeyPair>& key);

void AddKey(UINT key_num, UINT key_vk, std::string key_name, std::map <UINT, KeyPair>& key);

void RemoveKey(UINT key_num, std::map <UINT, KeyPair>& key);


