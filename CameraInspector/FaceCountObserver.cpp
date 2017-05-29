#include"FaceCountObserver.h"
#include "FileSystemFrameSaver.h"
#include<thread>
#include<iostream> // for Debug
#include<thread>
#include <string>

using namespace CameraInspector;
using namespace std;

FaceCountObserver::FaceCountObserver(std::shared_ptr<PhotoMaker> photo_maker): photo_maker_(photo_maker)
{
}

void FaceCountObserver::OnFaceQuantityChanged(size_t new_face_count)
{
	static unsigned short count_photos = 0;
	std::string name = std::to_string(++count_photos);

	dynamic_cast<FileSystemFrameSaver&>(*(photo_maker_->GetSaver())).SetNameToSave(name);
	photo_maker_->MakePhoto();
}