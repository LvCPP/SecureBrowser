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
	std::ofstream f("login_dialog_test_output.txt");

	An<WebCamController>()->RegisterForDeviceNotification();

	QApplication a(argc, argv);
	LoginDialog login_dialog;
	login_dialog.show();

	int result = a.exec();

	std::string cookies;
	login_dialog.GetMoodleSession(cookies);

	f << cookies;
	f.close();

	An<WebCamController>()->UnregisterForDeviceNotification();
	return result;
}