#include"HttpClient.h"
#include<iostream>

using namespace BrowserHttp;

int main(int argc, char* argv[])
{
	HttpClient client("https://www.google.com.ua");
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