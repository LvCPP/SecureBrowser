#pragma once

namespace SI
{

class SessionInstector
{
public:
	static bool IsCurrentSessionRemoteable();
	static bool IsInsideVBox();
};

}//namespace SI