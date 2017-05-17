#include <WebCamController.h>

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

	for (int i = 0; i < cam_count; ++i)
	{
		std::string used_camera = cameras_names.at(i);
		cv::namedWindow(used_camera);
			wcc->ActivateCamera(used_camera);

		do
		{
			Frame tmp_frame = wcc->GetFrame();
			cv::Mat mat(tmp_frame.GetRows(), tmp_frame.GetCols(), CV_8UC4, tmp_frame.GetData());
			cv::imshow(used_camera, mat);

		} while (cv::waitKey(27) != 27);
		
		cv::destroyWindow(used_camera);
	}

	system("pause");
	return 0;
}