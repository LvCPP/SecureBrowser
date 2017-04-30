#include "KeyList.h"

using namespace SecureBrowser;

// for printing non-alt key combinations
void KeyCombo::Print(const std::string& key_name)
{
	// printed in "keys.txt"
	std::ofstream key_file;
	key_file.open("keys.txt", std::ios::app);
	if (!key_file.is_open())
	{
		std::ofstream err_file;
		err_file.open("error.txt", std::ios::app);
		err_file << "Could not open the key_file!\n";
		err_file.close();
		return;
	}
	key_file << "[ ";
	if (this->ctrl)
		key_file << "CTRL ";
	if (this->shift)
		key_file << "SHIFT ";
	if (this->win)
		key_file << "WIN ";
	key_file << key_name << "] ";
		
	key_file.close();	
}

std::string KeyPair::GetKeyName()
{
	return (*this).name;
}
