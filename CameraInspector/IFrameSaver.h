#pragma once
#include <opencv2\highgui\highgui.hpp>

namespace CameraInspector
{

class IFrameSaver
{
public:
	virtual ~IFrameSaver() = default;
	virtual void Save(const cv::Mat& frame) = 0;
};

} // namespace CameraInspector