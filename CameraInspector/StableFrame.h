#pragma once
#include "Frame.h"

namespace CameraInspector
{

class StableFrame : public Frame
{
public:
	CI_API StableFrame();
	CI_API StableFrame(const StableFrame& sframe);
	CI_API StableFrame(const Frame& frame);
	CI_API StableFrame(int width, int height, void* data);
	CI_API StableFrame(const cv::Mat& mat);
	CI_API virtual ~StableFrame() = default;

	CI_API StableFrame& operator= (const StableFrame& sframe);
};

} // namespace CameraInspector