#include "FaceCountObserver.h"
#include "FileSystemFrameSaver.h"
#include <Logger.h>
#include <thread>
#include <iostream> // for Debug
#include <thread>
#include <string>

using namespace CameraInspector;
using namespace BrowserLogger;
using namespace Utils;
using namespace std;

FaceCountObserver::FaceCountObserver(std::shared_ptr<PhotoMaker> photo_maker)
	: photo_maker_(photo_maker)
{
}

void FaceCountObserver::OnFaceQuantityChanged(int new_face_count, const Frame& frame_to_save)
{
	static size_t previous_count;

#ifdef _DEBUG
	std::cout << "Previous: " << previous_count << std::endl;
	std::cout << "New: " << new_face_count << std::endl;
#endif //_DEBUG

	if ((previous_count != new_face_count) && (new_face_count != 1))
	{
		static unsigned short count_photos = 0;
		std::string name = std::to_string(++count_photos);

		logwarning(*An<Logger>()) << "Faces: " << new_face_count <<  ". Made photo with name " << name << ".jpg";

		dynamic_cast<FileSystemFrameSaver&>(*(photo_maker_->GetSaver())).Save(frame_to_save, name);
	}
	previous_count = new_face_count;
}