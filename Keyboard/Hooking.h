#pragma once

class Hooking // for various kinds of hooking
{
public:
	
	virtual ~Hooking();

	virtual void StartHooking() = 0;
	virtual void StopHooking() = 0;
};
