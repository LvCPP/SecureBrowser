#include "LoginApp2.h"
#include "LoginUtils.h"
#include <QApplication>

using namespace Login;


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	LoginApp2 w;
	w.show();

	return a.exec();
}
