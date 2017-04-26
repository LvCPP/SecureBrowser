#include "browser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Browser w;
	w.showMaximized();
	return a.exec();
}
