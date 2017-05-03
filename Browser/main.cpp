#include "browser.h"
#include <windows.h>
#include "LoginApp.hpp"
#include <QtWidgets/QApplication>

using namespace SecureBrowser;
using namespace BrowserLogin;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	
	Browser w;
	w.showMaximized();

	//LoginApp app;
	//app.show();

	return a.exec();
}