#pragma once
namespace SI
{

class IFakeWindowServiceObserver
{
public:
	virtual ~IFakeWindowServiceObserver() = default;
	virtual void EventHappened() = 0;
};

} // namespace SI