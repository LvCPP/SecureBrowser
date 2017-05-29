#pragma once

namespace CameraInspector
{
class IFaceDetectorObserver
{
public:
	virtual ~IFaceDetectorObserver() = default;
	virtual void OnFaceQuantityChanged(size_t face_count) = 0;
};
}