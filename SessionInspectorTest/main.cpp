#include "SessionInspector.h"
#include "FakeWindowService.h"
#include <iostream>

using namespace SI;

void main()
{
	FakeWindowService fws;
	std::cout << SessionInstector::IsCurrentSessionRemoteable();
	fws.Start();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	fws.Stop();
	system("pause");
}