#include "WebCameraCapture.h"
#include "PhotoMaker.h"
#include "FileSystemFrameSaver.h"
#include "FrameStorer.h"

#include <opencv2\highgui\highgui.hpp>

#include <Windows.h>
#include <iostream>

using namespace CameraInspector;

int main()
{
	WebCameraCapture& cam_cap = WebCameraCapture::Instance();

	cv::Mat frame_original;
	cv::String f_original_window = "Original";
	cv::String f_converted_window = "Converted";
	cv::namedWindow(f_original_window, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(f_converted_window, CV_WINDOW_AUTOSIZE);

	std::cout << "Height: " << cam_cap.GetCamera().get(CV_CAP_PROP_FRAME_HEIGHT)
		<< "\nWidth: " << cam_cap.GetCamera().get(CV_CAP_PROP_FRAME_WIDTH)
		<< "\nPress Esc to capture the screen" << std::endl;

	// Wait while camera initializes (don't need to do this on VS17)
	Sleep(500);

	while (cv::waitKey(30) != 27)
	{
		bool success = cam_cap.GetCamera().read(frame_original);

		if (!success)
		{
			std::cout << "Trouble capturing webcam!" << std::endl;
			system("pause");
			return -1;
		}

		imshow(f_original_window, frame_original);

		Frame my_frame(frame_original);
		cv::Mat frame_after(my_frame.GetImpl());

		imshow(f_converted_window, frame_after);
	}

	cv::destroyWindow(f_original_window);
	cv::destroyWindow(f_converted_window);
	// -----------------------------------------------------------------------------------------------------------------------------

	std::shared_ptr<IFrameSaver> shared_saver = std::make_shared<FileSystemFrameSaver>(FileSystemFrameSaver());
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetPathToSave("");

	// Create & configure maker
	std::shared_ptr<PhotoMaker> shared_maker = std::make_shared<PhotoMaker>(PhotoMaker());
	shared_maker->SetFrameSaver(shared_saver);

	cam_cap.AddFrameHandler(shared_maker);
	cam_cap.Start();

	cv::Mat id_frame;
	cam_cap.GetCamera().read(id_frame);
	FrameStorer store_id(id_frame);

	cv::namedWindow("Stored frame");
	cv::imshow("Stored frame", store_id.Get().GetImpl());
	cv::waitKey(0);
	
	// User approves
	cv::destroyWindow("Stored frame");	
	dynamic_cast<FileSystemFrameSaver&>(*shared_saver).SetNameToSave("ID");	// optional
	store_id.Save(shared_saver);

	// During test
	dynamic_cast<FileSystemFrameSaver*>(shared_saver.get())->SetNameToSave("shot_01");
	shared_maker->MakePhoto();
	Sleep(100);
	std::cout << "Another photo saved!" << std::endl;

	cam_cap.Stop();

	system("pause");
	return 0;
}
