#pragma once

class IObserver
{
public:
	virtual void OnFaceQuantityChanged(int face_count) = 0;
};
