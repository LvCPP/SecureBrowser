#include "WebCameraCapture.h"
#include "PhotoMaker.h"
#include "FileSystemFrameSaver.h"
#include "FrameStorer.h"

#include <opencv2\highgui\highgui.hpp>

#include <Windows.h>
#include <iostream>

using namespace CameraInspector;

void TImitFPS(cv::VideoCapture& video, PhotoMaker& maker);

bool g_imit = true;

int main()
{
	cv::VideoCapture video(0);
	cv::Mat frame_original;

	cv::String f_original_window = "Original";
	cv::String f_converted_window = "Converted";
	cv::namedWindow(f_original_window, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(f_converted_window, CV_WINDOW_AUTOSIZE);

	std::cout << "Height: " << video.get(CV_CAP_PROP_FRAME_HEIGHT)
		<< "Width: " << video.get(CV_CAP_PROP_FRAME_WIDTH)
		<< "Press Esc to capture the screen" << std::endl;

	// Wait while camera initializes (don't need to do this on VS17)
	Sleep(500);

	while (cv::waitKey(30) != 27)
	{
		bool success = video.read(frame_original);

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

	std::shared_ptr<IFrameSaver> share_saver = std::make_shared<FileSystemFrameSaver>(FileSystemFrameSaver());
	dynamic_cast<FileSystemFrameSaver&>(*share_saver).SetPathToSave("");

	// Create & configure maker
	PhotoMaker maker;
	maker.SetFrameSaver(share_saver);

	// Create & configure camera
	WebCameraCapture camera_01;
	std::shared_ptr<IFrameHandler> share_maker = std::make_shared<PhotoMaker>(maker);
	camera_01.AddFrameHandler(share_maker);
	camera_01.Start();

	// Imitate camera capture work
	std::thread imit_fps = std::thread(TImitFPS, std::ref(video), std::ref(maker));

	/*	User ID photo. Possible use example
	FrameStorer id_photo(camera_01.GetFrame());
	cv::imshow("ID", id_photo.Get().GetImpl());			// user doesn't like this and want another	(Cancel button)
	
	id_photo = FrameStorer(camera_01.GetFrame());
	cv::imshow("ID", id_photo.Get().GetImpl());			// user like it, we want to save			(OK button)
	FrameStorer.Save(share_saver);
	*/

	cv::Mat id_frame;
	video.read(id_frame);
	FrameStorer store_id(id_frame);

	cv::namedWindow("Stored frame");
	cv::imshow("Stored frame", store_id.Get().GetImpl());
	cv::waitKey(0);
	
	// User approves
	cv::destroyWindow("Stored frame");	
	dynamic_cast<FileSystemFrameSaver&>(*share_saver).SetNameToSave("ID");	// optional
	store_id.Save(share_saver);

	// During test
	dynamic_cast<FileSystemFrameSaver*>(share_saver.get())->SetNameToSave("shot_01");
	maker.MakePhoto();
	Sleep(100);
	std::cout << "Another photo saved!" << std::endl;

	camera_01.Stop();
	g_imit = false;
	
	if(imit_fps.joinable())
		imit_fps.join();

	system("pause");
	return 0;
}

void TImitFPS(cv::VideoCapture& video, PhotoMaker& maker)
{
	cv::Mat tmp_frame;
	
	while (g_imit)
	{
		if (!video.read(tmp_frame))
		{
			std::cout << "Trouble capturing webcam!" << std::endl;
			system("pause");
			exit(-1);
		}
		maker.ProcessFrame(Frame(tmp_frame));
		
		// 20 FPS
		Sleep(50);
	}
}
