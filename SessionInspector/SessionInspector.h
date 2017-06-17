#pragma once

namespace SI
{

class SessionInspector
{
public:
	static bool IsCurrentSessionRemoteable();
	static bool IsInsideVBox();
};

} // namespace SI