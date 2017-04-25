#pragma once
#include "IFrameHandler.h"
#include "IObservable.h"
#include "Frame.h"
#include "opencv2/objdetect/objdetect.hpp"

namespace CameraInspector
{

class FaceDetector : public IFrameHandler, public IObservable
{
public:
	FaceDetector();
	virtual ~FaceDetector() = default;
	bool Load();//Loads a classifier from a file.
	void ProcessFrame(const Frame& frame) override;
private:
	cv::CascadeClassifier face_cascade;
	std::string face_cascade_name;
};

} // namespace CameraInspector