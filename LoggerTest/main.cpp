#include <iostream>
#include <Logger.h>
#include <fstream>

using namespace SecureBrowser;

int main()
{
	//Logger inst; //write to std::cout with min_level DEBUG (lowest level)

	Logger inst(LogLevel::Info); //write to std::cout with min_level INFO

	//std::ofstream file("log.txt", std::ios::app);
	//Logger inst(LogLevel::Info, file); //write to file with min_level INFO don't close file,
		//Logger do it automatically
	
	inst << LogLevel::Error << "Hello, world! #" << 555 << 123;
	inst << LogLevel::Warning << "123";
	inst << LogLevel::Info << "Info";
	inst << LogLevel::Debug << "I'm will be invisible, because Debug < Info";
}
