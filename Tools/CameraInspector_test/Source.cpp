#include "WebCameraCapture.h"
#include "PhotoMaker.h"
#include "FileSystemFrameSaver.h"

#include <opencv2\highgui\highgui.hpp>

#include <Windows.h>
#include <iostream>

using namespace CameraInspector;

int main()
{
	cv::VideoCapture video(0);
	cv::Mat frame_original;
	Frame my_frame;

	cv::String f_original_window = "Original";
	cv::String f_converted_window = "Converted";
	cv::namedWindow(f_original_window, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(f_converted_window, CV_WINDOW_AUTOSIZE);

	std::cout << "Height: " << video.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
	std::cout << "Width: " << video.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
	std::cout << "Press Esc to capture the screen" << std::endl;

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

		my_frame.Construct(frame_original.cols, frame_original.rows, frame_original.data);
		cv::Mat frame_after(my_frame.GetRows(), my_frame.GetCols(), CV_8UC3, my_frame.GetData());

		imshow(f_converted_window, frame_after);
	}

	cv::destroyWindow(f_original_window);
	cv::destroyWindow(f_converted_window);
	// -----------------------------------------------------------------------------------------------------------------------------

	// Create & configure saver
	FileSystemFrameSaver saver;
	saver.SetPathToSave("");

	// Create & configure maker
	PhotoMaker maker;
	std::shared_ptr<IFrameSaver> share_saver = std::make_shared<FileSystemFrameSaver>(saver);
	maker.SetPhotoSaver(share_saver);

	//	maker.SetPhotoSaver(std::shared_ptr<IFrameSaver>(&saver));

	// Create & configure camera
	WebCameraCapture camera_01;
	std::shared_ptr<IFrameHandler> share_maker = std::make_shared<PhotoMaker>(maker);
	camera_01.AddFrameHandler(share_maker);
	camera_01.Start();

	// maker we will get from camera_01
	maker.ProcessFrame(my_frame);				// or maker.MakePhoto(frame); - without saving it
	maker.MakePhoto();
	std::cout << "Photo saved!" << std::endl;

	// ...

	camera_01.Stop();

	system("pause");
	return 0;
}