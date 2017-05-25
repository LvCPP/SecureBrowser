#pragma once
#include <windows.h>
#include <Wtsapi32.h>

namespace SI
{

class FakeWindowService
{
public:
	static void MakeFakeWindow();
};

}