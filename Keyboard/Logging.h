#pragma once
#include <string>
#include <fstream>

class Logging
{
public:
	
	void Print(std::string key_name, std::string file_name);
	
private:
	std::string key_name;
	std::string file_name;
};
