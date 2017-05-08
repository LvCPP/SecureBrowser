#ifndef BROWSER_H
#define BROWSER_H

#include <QtWidgets/QMainWindow>
#include "ui_browser.h"

class Browser : public QMainWindow
{
	Q_OBJECT

public:
	Browser(QWidget *parent = 0);
	~Browser();

private:
	Ui::BrowserClass ui;
};

#endif // BROWSER_H
