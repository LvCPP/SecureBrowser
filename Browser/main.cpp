#include "browser.h"
#include <LoginApp.h>
#include <Logger.h>
#include <LoginApp2.h>
#include <WebCamController.h>
#include <windows.h>
#include <fstream>
#include <QtWidgets/QApplication>

using namespace CameraInspector;
using namespace SecureBrowser;
using namespace BrowserLogin;
using namespace BrowserLogger;
using namespace Utils;
using namespace Login;

int main(int argc, char* argv[])
{
	An<Logger> logger;
	std::ofstream file("log.txt", std::ios::out);
	logger->SetOutput(file);

	loginfo(*logger) << "Program initialized";
	
	QApplication a(argc, argv);
	LoginApp2 app;
	
	loginfo(*logger) << "Start login";
	if (!app.exec())
	{
		logerror(*logger) << "User aborted logging in. Finish program.";
		logger->Flush();
		file.close();
		return 0;
	}

	loginfo(*logger) << "User loged in. Start Browser";
	Browser w;
	w.showMaximized();
	int result = a.exec();

	loginfo(*logger) << "Program finished with code " << result;
	logger->Flush();
	file.close();
	return result;
}