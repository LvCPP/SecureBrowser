#include "test.h"
#include <QtWidgets/QApplication>

#include "../WI/WindowsInspector.h"

using namespace SBWindowsInspector;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Test w;

	WindowsInspector wi;
	wi.StartWindowsInspector();

	w.show();
	return a.exec();
}
