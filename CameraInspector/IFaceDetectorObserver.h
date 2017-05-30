#pragma once
#include "CameraInspectorUtils.h"

namespace CameraInspector
{
class IFaceDetectorObserver
{
public:
	CI_API virtual ~IFaceDetectorObserver() = default;
	CI_API virtual void OnFaceQuantityChanged(int face_count) = 0;
};
}