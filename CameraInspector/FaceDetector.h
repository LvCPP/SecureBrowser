#pragma once
#include "IFrameHandler.h"
#include "Frame.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace CameraInspector
{

class FaceDetector : public IFrameHandler
{
public:
	FaceDetector();
	virtual ~FaceDetector() = default;

	void ProcessFrame(Frame frame) override;

	cv::CascadeClassifier face_cascade;
	std::string face_cascade_name;
	std::string window_name;
};

} // namespace CameraInspector