#include "browser.h"
#include <windows.h>
#include "LoginApp.hpp"
#include <QtWidgets/QApplication>

using namespace SecureBrowser;
using namespace BrowserLogin;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	LoginApp app;
	if (!app.exec())
		return 0; 
	Browser w;
	w.showMaximized();
	return a.exec();
}