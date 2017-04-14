#pragma once
#include "IFrameHandler.h"

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	FaceDetector();
	virtual ~FaceDetector() = default;

	// Interface :). Calls 'work' function inside
	void ProcessFrame(cv::Mat frame) override;
};

} // namespace CameraInspector