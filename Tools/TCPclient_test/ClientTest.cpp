// ClientTest.cpp : Defines the entry point for the console application.
//
#include <Client.h>
#include <An.hpp>
#include <iostream>
#include <string>

using namespace TCP_client;
using namespace Utils;

int main()
{
	An<Client> c;

	std::string s;
	c->GetConfig(s);
	c->SendFile("D:\\SS\\master\\alpaca.jpg", "");

	std::cout << s;
	return 0;
}

