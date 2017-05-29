#include "WebCamController.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <exception>
#include <thread>

using namespace CameraInspector;
using namespace Utils;

bool g_is_working;

void ShowDevices(unsigned int delay_ms);

int main() 
{
	g_is_working = true;
	std::thread shower = std::thread(&ShowDevices, 1500);

	An<WebCamController> wcc;
	std::vector<WebCam>& cameras_ = wcc->GetCameras();
	wcc->ActivateCamera(cameras_.at(0));

	cv::namedWindow("test cameras UI");
	int choose = -1;

	while(choose != 113)
	{
		choose = cv::waitKey(10);

		try
		{
			Frame tmp_frame = wcc->GetActiveCamera().GetFrame();
			cv::Mat mat(tmp_frame.GetRows(), tmp_frame.GetCols(), CV_8UC4, tmp_frame.GetData());
			cv::imshow("test cameras UI", mat);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}

		switch (choose)
		{
		case 113: //reserved for q = exit
		case -1: // no key pressed
			break;
		case 27:
			wcc->Refresh();
			break;
		case 49:
		case 50:
		case 51:
			wcc->ActivateCamera(cameras_.at(choose - 49));
			break;
		default:
			std::cout << "Bad command: " << choose << std::endl;
			break;
		}
	}
	
	cv::destroyWindow("test cameras UI");

	g_is_working = false;
	if (shower.joinable())
		shower.join();

	system("pause");
	return 0;
}

void ShowDevices(unsigned int delay_ms)
{
	std::vector<WebCam>& cameras_ = An<WebCamController>()->GetCameras();

	while (g_is_working)
	{
		system("cls");

		for (WebCam cam : cameras_)
			std::cout << cam.GetName() << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
	}
}
