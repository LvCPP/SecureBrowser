#pragma once
#include "CameraInspectorUtils.h"

namespace CameraInspector
{

class Frame;

class IFrameHandler
{
public:
	CI_API virtual ~IFrameHandler() = default;
	CI_API virtual void ProcessFrame(const Frame& frame) = 0;
};

} // namespace CameraInspector