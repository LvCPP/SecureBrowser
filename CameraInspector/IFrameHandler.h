#pragma once

namespace CameraInspector
{

class Frame;

class IFrameHandler
{
public:
	virtual ~IFrameHandler() = default;
	// Frame can be modified in handler class, so we need to copy it
	// Calls <fps> times per second
	virtual void ProcessFrame(Frame frame) = 0;
};

} // namespace CameraInspector