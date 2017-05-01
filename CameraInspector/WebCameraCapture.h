#pragma once
#include "IFrameHandler.h"

#include <memory>
#include <vector>

namespace CameraInspector
{

class WebCameraCapture
{
public:
	void Start();
	void Stop();
	// Frame handlers. This class instance can call they for different purposes
	void AddFrameHandler(const std::shared_ptr<IFrameHandler>& handler);

private:
	std::vector<std::shared_ptr<IFrameHandler>> handlers_;
};

} // namespace CameraInspector