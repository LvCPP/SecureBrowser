#include "IObservable.h"
#include "IObserver.h"

void IObservable::Attach(IObserver* observer)
{
	observers.push_back(observer);
}

void IObservable::Detach(IObserver* observer)
{
	observers.remove(observer);
}

void IObservable::Notify(int face_count)
{
	for (IObserver* obs : observers)
	{
		obs->OnFaceQuantityChanged(face_count);
	}
}