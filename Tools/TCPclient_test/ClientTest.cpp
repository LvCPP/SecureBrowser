// ClientTest.cpp : Defines the entry point for the console application.
//
#include <Client.h>
#include <iostream>

int main()
{
	Client c("127.0.0.1");

	std::string s;
	c.get_config(s);
	c.send_file("D:\\SS\\master\\alpaca.jpg", "");

	std::cout << s;
	return 0;
}

