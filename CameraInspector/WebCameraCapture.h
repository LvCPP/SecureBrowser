#pragma once
#include "IFrameHandler.h"

#include <memory>

namespace CameraInspector
{

class WebCameraCapture
{
public:
	// Starts capturing the camera
	// Means it starts recieving and(if needed) processing images(frames) from the DirectShow module
	void Start();
	// Stops capturing the camera
	void Stop();
	// Frame handlers. This class instance can call they for different purposes
	void AddFrameHandler(std::shared_ptr<IFrameHandler>& handler);

private:
	std::vector<std::shared_ptr<IFrameHandler>> handlers_;
};

} // namespace CameraInspector