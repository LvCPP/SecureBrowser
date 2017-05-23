#include "WebCamController.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace CameraInspector;
using namespace Utils;

int main() 
{
	An<WebCamController> wcc;

	std::vector<std::string> cameras_names = wcc->ListNamesOfCameras();

	for (std::string name : cameras_names)
		std::cout << name << std::endl;

	auto cam_count = wcc->GetCamerasCount();

	cv::namedWindow("test cameras UI");
	int choose = -1;

	wcc->ActivateCamera(cameras_names.at(0));

	while (true)
	{

		Frame tmp_frame = wcc->GetFrame();
		cv::Mat mat(tmp_frame.GetRows(), tmp_frame.GetCols(), CV_8UC4, tmp_frame.GetData());
		cv::imshow("test cameras UI", mat);

		switch (choose = cv::waitKey(10))
		{
		case -1:
			break;
		case 27:
		{
			wcc->Refresh();

			cameras_names = wcc->ListNamesOfCameras();

			for (std::string name : cameras_names)
				std::cout << name << std::endl;

			wcc->ActivateCamera(cameras_names.at(0));

			break;
		}
		case 49:
		case 50:
		case 51:
			wcc->ActivateCamera(cameras_names.at(choose - 49));
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