#pragma once
#include "Frame.h"

namespace CameraInspector
{

class StableFrame :
	public Frame
{
public:
	StableFrame();
	StableFrame(const StableFrame& sframe);
	StableFrame(const Frame& frame);
	StableFrame(int width, int height, void* data);
	StableFrame(const cv::Mat& mat);
	virtual ~StableFrame() = default;

	StableFrame& operator= (const StableFrame& sframe);
};

} // namespace CameraInspector