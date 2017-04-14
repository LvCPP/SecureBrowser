#pragma once
#include <opencv2\highgui\highgui.hpp>

namespace CameraInspector
{

class IFrameSaver
{
public:
	virtual ~IFrameSaver() = default;
	virtual void SaveFrame(const cv::Mat& frame) = 0;
	virtual void SaveFrame(const cv::Mat& frame, const std::string& name) = 0;
};

} // namespace CameraInspector