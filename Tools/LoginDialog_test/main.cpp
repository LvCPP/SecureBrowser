#include "LoginDialog.h"
#include <An.hpp>
#include <WebCamController.h>
#include <QtWidgets/QApplication>

using namespace Utils;
using namespace CameraInspector;
using namespace Login;

int main(int argc, char *argv[])
{
	An<WebCamController>()->RegisterForDeviceNotification();

	QApplication a(argc, argv);
	
	LoginDialog login_dialog("lv-28-226215", "Z7_7_P", "3257", "231", argv[0]);
	login_dialog.show();
	
	int result = a.exec();

	An<WebCamController>()->UnregisterForDeviceNotification();
	return result;
}