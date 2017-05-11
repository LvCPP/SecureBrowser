#include "browser.h"
#include <windows.h>
#include "LoginApp.h"
#include <Logger.h>
#include <fstream>
#include <QtWidgets/QApplication>

using namespace SecureBrowser;
using namespace BrowserLogin;
using namespace BrowserLogger;
using namespace Utils;

int main(int argc, char* argv[])
{
	An<Logger> logger;
	std::ofstream file("log.txt", std::ios::out);
	logger->SetOutput(file);

	loginfo(*logger) << "Program initialized";
	QApplication a(argc, argv);
	LoginApp app;
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