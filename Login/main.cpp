#include"LoginWidget.hpp"
#include"LoginCamera.hpp"
#include"LoginApp.hpp"
#include"LoginDialog.hpp"
#include<QtWidgets/QApplication>
#include<iostream>
using namespace BrowserLogin;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LoginDialog app;
	app.exec();
	return a.exec();
}
