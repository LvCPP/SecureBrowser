// ClientTest.cpp : Defines the entry point for the console application.
//
#include <Client.h>
#include <iostream>
#include <string>

using namespace TCP_client;

int main()
{
	Client c("10.4.55.13");

	std::string s;
	c.GetConfig(s);
	c.SendFile("D:\\SS\\master\\alpaca.jpg", "");

	std::cout << s;
	return 0;
}

