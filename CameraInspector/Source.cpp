#include "WebCameraCapture.h"
#include "PhotoMaker.h"
#include "FileSystemFrameSaver.h"
#include "Frame.h"

#include <Windows.h>
#include <iostream>

using namespace CameraInspector;

int main() 
{
	cv::VideoCapture video(0);
	cv::Mat frame_original;
	Frame my_frame;

	cv::String original_window = "Original";
	cv::String converted_window = "Converted";
	cv::namedWindow(original_window, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(converted_window, CV_WINDOW_AUTOSIZE);

	std::cout << "Height: " << video.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
	std::cout << "Width: " << video.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
	std::cout << "Press Esc to take screen" << std::endl;

	// Wait while camera initializes (don't need to do this on VS17)
	Sleep(1000);

	while (cv::waitKey(30) != 27)
	{
		bool success = video.read(frame_original);

		if (!success)
		{
			std::cout << "Trouble capturing webcam!" << std::endl;
			system("pause");
			exit(-1);
		}

		imshow(original_window, frame_original);

		my_frame.Construct(frame_original.rows, frame_original.cols, frame_original.data);
		cv::Mat frame_after(my_frame.GetRows(), my_frame.GetCols(), CV_8UC3, my_frame.GetData());

		imshow(converted_window, frame_after);
	}

	cv::destroyWindow(original_window);
	cv::destroyWindow(converted_window);

	cv::Mat frame(my_frame.GetRows(), my_frame.GetCols(), CV_8UC3, my_frame.GetData());		// ensure that conversion works fine
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
	maker.ProcessFrame(frame);				// or maker.MakePhoto(frame); - without saving it
	maker.MakePhoto();				

	// ...

	camera_01.Stop();																		
			
	system("pause");
 	return 0;
}