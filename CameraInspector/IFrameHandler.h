#pragma once

namespace CameraInspector
{

class Frame;

class IFrameHandler
{
public:
	virtual ~IFrameHandler() = default;
	virtual void ProcessFrame(const Frame& frame) = 0;
};
} // namespace CameraInspector