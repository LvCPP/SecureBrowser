#pragma once
#include "Frame.h"

namespace CameraInspector
{

class IFaceDetectorObserver
{
public:
	virtual ~IFaceDetectorObserver() = default;
	virtual void OnFaceQuantityChanged(int face_count, const Frame& frame_to_save) = 0;
};

} // namespace CameraInspector