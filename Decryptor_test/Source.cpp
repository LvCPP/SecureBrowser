#include <Base64Decryptor.h>
#include <iostream>

using namespace Decryptor;

int main()
{
	// Smth simple
	std::string s1("Njc0MTk5DQpUaGlzIGlzIGEgcGFzc3dvcmQuIEhlcmUgY2FuIGJlIGFueXRoaW5nLg");

	std::cout << Base64Decryptor::Decode(s1) << std::endl;

	// Crash-test
	std::string s2("QmFzZTY0IGlzIGEgZ3JvdXAgb2Ygc2ltaWxhciBiaW5hcnktdG8tdGV4dCBlbmNvZGlu"
		"ZyBzY2hlbWVzIHRoYXQgcmVwcmVzZW50IGJpbmFyeSBkYXRhIGluIGFuIEFTQ0lJIHN0cmluZyBmb3J"
		"tYXQgYnkgdHJhbnNsYXRpbmcgaXQgaW50byBhIHJhZGl4LTY0IHJlcHJlc2VudGF0aW9uLiBUaGUgdG"
		"VybSBCYXNlNjQgb3JpZ2luYXRlcyBmcm9tIGEgc3BlY2lmaWMgTUlNRSBjb250ZW50IHRyYW5zZmVyI"
		"GVuY29kaW5nIQ");

	std::cout << Base64Decryptor::Decode(s2) << std::endl;

	system("pause");
	return 0;
}