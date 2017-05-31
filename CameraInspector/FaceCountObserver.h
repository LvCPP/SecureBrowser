#pragma once
#include"IFaceDetectorObserver.h"
#include<memory>
#include"PhotoMaker.h"

namespace CameraInspector
{

class FaceCountObserver : public IFaceDetectorObserver
{
public:
	CI_API FaceCountObserver(std::shared_ptr<PhotoMaker> photo_maker);
	CI_API void OnFaceQuantityChanged(int face_count, const Frame& frame_to_save);

private:
	std::shared_ptr<PhotoMaker> photo_maker_;
};

}