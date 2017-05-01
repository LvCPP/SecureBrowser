#pragma once

namespace CameraInspector
{
class IFaceDetectorObserver
{
public:
	virtual ~IFaceDetectorObserver() = default;
	virtual void OnFaceQuantityChanged(int face_count) = 0;
};
}