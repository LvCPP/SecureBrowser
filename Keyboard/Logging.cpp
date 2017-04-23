#include "Logging.h"


void Logging::Print(std::string key_name, std::string file_name = "keys.txt")
{
	std::ofstream file;
	file.open(file_name, std::ios::ate);
	file << key_name;
	file.close();
}




