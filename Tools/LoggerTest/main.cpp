#include <Logger.h>
#include <fstream>
#include<functional>

using namespace BrowserLogger;

std::string UserFormat(const LogMessage& message)
{
	std::stringstream formatted_message;
	formatted_message << "[" << GetFormattedTime() << "]" 
		<< " with level " << log_level_name.at(message.level) << ". Message: " 
		<< message.message << std::endl;
	return formatted_message.str();
}

//Logger inst(LogLevel::Info, file, "[%D at %T] with level %L. Message: %M. KEK");

int main()
{
	//Logger inst; //write to std::cout with min_level DEBUG (lowest level)
	//Logger inst(LogLevel::Info); //write to std::cout with min_level INFO

	//std::ofstream file("log.txt", std::ios::out);
	//Logger inst(LogLevel::Info, file); //write to file with min_level INFO
	
	Logger inst(LogLevel::Info, std::cout, UserFormat);

	inst << LogLevel::Error << "Hello, world! #" << 555 << 123;
	inst << LogLevel::Warning << "123";
	inst << LogLevel::Info << "Info";
	inst << LogLevel::Debug << "I'm will be invisible, because Debug < Info";

	inst.Flush();
	//file.close();
}
