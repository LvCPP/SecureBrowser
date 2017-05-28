#include "LoginApp2.h"
#include "LoginUtils.h"
#include <QApplication>

using namespace Login;

//#include "WebCamController.h"
//#include "WebCam.h"
//#include "Frame.h"
//#include <An.hpp>
//#include "escapi.h"
//#include <vector>
//#include <string>
//#include <mutex>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//#include <exception>

//using namespace CameraInspector;
//using namespace Utils;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*An<WebCamController> wcc;
	std::vector<WebCam>& cameras_ = wcc->GetCameras();*/

	LoginApp2 w;
	w.show();

	return a.exec();
}
