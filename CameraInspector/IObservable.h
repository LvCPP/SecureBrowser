#pragma once
#include <list>

class IObserver;

class IObservable
{
public:
	void Attach(IObserver* observer);
	void Detach(IObserver* observer);
protected:
	void Notify(int face_count);

	std::list<IObserver*> observers;
};