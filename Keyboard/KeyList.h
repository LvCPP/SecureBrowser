#pragma once
#include <windows.h>
#include <map>
#include <iostream>
#include <fstream>

class KeyPair
{
public:
	KeyPair() {}
	KeyPair(UINT vk_code, std::string key_name) : vk(vk_code), name(key_name) {}
	std::string GetKeyName();
private:
	UINT vk;
	std::string name;
};
