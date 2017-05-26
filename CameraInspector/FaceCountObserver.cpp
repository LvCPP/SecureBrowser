#include"FaceCountObserver.h"
#include<thread>
#include<iostream> // for Debug
#include<thread>
using namespace CameraInspector;
using namespace std;

FaceCountObserver::FaceCountObserver(): photo_maker_(make_shared<PhotoMaker>())
{
}

void FaceCountObserver::OnFaceQuantityChanged(size_t new_face_count)
{
	photo_maker_->MakePhoto();
}