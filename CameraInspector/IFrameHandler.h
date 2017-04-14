#pragma once
#include <opencv2\highgui\highgui.hpp>

namespace CameraInspector
{

class IFrameHandler
{
public:
	virtual ~IFrameHandler() = default;
	// Frame can be modified in handler class, so we need to copy it
	virtual void ProcessFrame(cv::Mat frame) = 0;
};

} // namespace CameraInspector