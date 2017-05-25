#include "WebCamController.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <exception>

using namespace CameraInspector;
using namespace Utils;

int main() 
{
	An<WebCamController> wcc;

	std::vector<WebCam> cameras_ = wcc->GetCameras();

	for (WebCam cam : cameras_)
		std::cout << cam.GetName() << std::endl;

	auto cam_count = wcc->GetCamerasCount();

	cv::namedWindow("test cameras UI");
	int choose = -1;

	wcc->ActivateCamera(cameras_.at(0));

	while (cv::waitKey(10) != 113)
	{
		try
		{
			Frame tmp_frame = wcc->GetActiveCamera().GetFrame();

			cv::Mat mat(tmp_frame.GetRows(), tmp_frame.GetCols(), CV_8UC4, tmp_frame.GetData());
			cv::imshow("test cameras UI", mat);
		}
		catch (std::exception ex)
		{
			std::cout << ex.what() << std::endl;
		}

		switch (choose = cv::waitKey(10))
		{
		case -1:
			break;
		case 27:
		{
			wcc->Refresh();

			for (WebCam cam : cameras_)
				std::cout << cam.GetName() << std::endl;

			break;
		}
		case 49:
		case 50:
		case 51:
			wcc->ActivateCamera(cameras_.at(choose - 49));
			break;
		default:
			std::cout << "Bad command: " << choose << std::endl;
			choose = -1;
			break;
		}

	}
	
	cv::destroyWindow("test cameras UI");

	system("pause");
	return 0;
}