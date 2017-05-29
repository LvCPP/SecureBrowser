#include "WebCameraCapture.h"
#include "PhotoMaker.h"
#include "FileSystemFrameSaver.h"
#include "FrameStorer.h"
#include "FaceDetector.h"
#include "FaceCountObserver.h"

#include <opencv2\highgui\highgui.hpp>		// used only for displaying images and input control

#include <Windows.h>
#include <iostream>
#include <thread>


using namespace CameraInspector;
using namespace Utils;
using namespace std;

int TestPhotoMaker()
{
	An<WebCameraCapture> cam_cap;

	cv::String f_converted_window = "Converted";
	cv::namedWindow(f_converted_window, CV_WINDOW_AUTOSIZE);
	
	std::cout << "\nPress Esc to capture the screen" << std::endl;

	char choose = 0;
	while (cv::waitKey(30) != 27)
	{
		Frame tmp_frame = cam_cap->GetCurrentStableFrame();
		cv::Mat to_show(tmp_frame.GetImpl());
		imshow(f_converted_window, to_show);
	}

	cv::destroyWindow(f_converted_window);
	// -----------------------------------------------------------------------------------------------------------------------------

	std::shared_ptr<IFrameSaver> shared_saver = std::make_shared<FileSystemFrameSaver>(FileSystemFrameSaver());
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetPathToSave("");

	// Create & configure maker
	std::shared_ptr<PhotoMaker> shared_maker = std::make_shared<PhotoMaker>(PhotoMaker());
	shared_maker->SetFrameSaver(shared_saver);

	cam_cap->AddFrameHandler(shared_maker);
	cam_cap->Start();

	FrameStorer storer = cam_cap->GetCurrentStableFrame();

	cv::namedWindow("Stored frame");
	cv::imshow("Stored frame", storer.Get().GetImpl());
	cv::waitKey(0);
	
	// Suppose, user approves
	cv::destroyWindow("Stored frame");	
	
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetNameToSave("ID");	// optional
	storer.Save(shared_saver);

	// During test ...
	dynamic_cast<FileSystemFrameSaver*>(shared_saver.get())->SetNameToSave("shot_01");
	shared_maker->MakePhoto();
	std::cout << "Another photo saved!" << std::endl;

	cam_cap->Stop();

	return 0;
}

void TestFaceDetector()
{
	An<WebCameraCapture> cam_cap;

	const std::shared_ptr<FaceDetector> face_detector = std::make_shared<FaceDetector>();

	std::shared_ptr<IFrameSaver> shared_saver = std::make_shared<FileSystemFrameSaver>(FileSystemFrameSaver());
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetPathToSave("");
	std::shared_ptr<PhotoMaker> shared_maker = std::make_shared<PhotoMaker>(PhotoMaker());
	shared_maker->SetFrameSaver(shared_saver);

	const std::shared_ptr<FaceCountObserver> observer = std::make_shared<FaceCountObserver>(shared_maker);
	face_detector->Attach(observer);

	cam_cap->AddFrameHandler(face_detector);
	cam_cap->AddFrameHandler(shared_maker);
	face_detector->SetFrequency(3s);
	cam_cap->Start();
	std::this_thread::sleep_for(std::chrono::seconds(20000));
	cam_cap->Stop();
}

int main(int argc, char** argv)
{
	TestFaceDetector();
	system("pause");
	return 0;
}

//int main(int argc, char** argv)
//{
//	if (argc != 2)
//	{
//		return -1;
//	}
//
//	const std::string select = argv[1];
//	if (select == "photo")
//	{
//		TestPhotoMaker();
//	}
//	else if (select == "face")
//	{
//		TestFaceDetector();
//	}
//	else
//	{
//		std::cout << "bad_choise" << std::endl;
//	}
//
//    system("pause");
//	return 0;
//}
