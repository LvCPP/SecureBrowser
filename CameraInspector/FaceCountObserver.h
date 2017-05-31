#pragma once
#include"IFaceDetectorObserver.h"
#include<memory>
#include"PhotoMaker.h"

namespace CameraInspector
{

class FaceCountObserver : public IFaceDetectorObserver
{
public:
	FaceCountObserver(std::shared_ptr<PhotoMaker> photo_maker);
	void OnFaceQuantityChanged(size_t face_count);

private:
	std::shared_ptr<PhotoMaker> photo_maker_;
};

}