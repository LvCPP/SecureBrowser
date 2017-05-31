#pragma once
#include "CameraInspectorUtils.h"

namespace CameraInspector
{

class Frame;

class IFrameSaver
{
public:
	CI_API virtual ~IFrameSaver() = default;
	CI_API virtual void Save(const Frame& frame) = 0;
};

} // namespace CameraInspector