#include "LoginDialog.h"
#include <An.hpp>
#include <WebCamController.h>
#include <QtWidgets/QApplication>

#include <iostream>
#include <fstream>
#include <string>

using namespace Utils;
using namespace CameraInspector;
using namespace Login;

int main(int argc, char *argv[])
{
	std::ofstream f("out2.txt");

	An<WebCamController>()->RegisterForDeviceNotification();

	QApplication a(argc, argv);
	LoginDialog login_dialog;
	login_dialog.show();

	std::string cookies;
	login_dialog.CheckLogin(cookies);
	
	f << cookies;
	f.close();


	int result = a.exec();

	An<WebCamController>()->UnregisterForDeviceNotification();
	return result;
}