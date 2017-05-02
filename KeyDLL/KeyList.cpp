#include "KeyList.h"

using namespace Keyboard;

std::string KeyPair::GetKeyName()
{
	std::map <UINT, KeyPair>::iterator it = key_map.find((*this).vk);
	if (it == key_map.end())
		return std::to_string((*this).vk);
	else
		return (*this).name;
}
