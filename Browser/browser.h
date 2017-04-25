#ifndef BROWSER_H
#define BROWSER_H

#include <QtWidgets/QWidget>
#include "ui_browser.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QUrl>
#include <QDebug>

class Browser : public QWidget
{
	Q_OBJECT

public:
	Browser(QWidget *parent = 0);
	~Browser();

private slots:

	void slotEnter();       // For Enter in LineEdit
	void slotLinkClicked(QUrl url); // For clicked URL

private:
	Ui::BrowserClass *ui;
};

#endif // BROWSER_H
