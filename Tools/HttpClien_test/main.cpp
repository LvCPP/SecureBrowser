#include"HttpClient.h"
#include<iostream>

using namespace Http;

int main(int argc, char* argv[])
{
	HttpClient client;
	try
	{
		auto response = client.Get("/");
	}
	catch (const std::exception &e)
	{
		std::cout << "Error exception: " << e.what() << '\n';
	}
	system("pause");
	return 0;
}