#pragma once

#include "ui_browser.h"
#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QWebEngineView>
#include <QUrl>
#include <QDebug>
#include <QWebEnginePage>
#include <memory>


class Browser : public QWidget
{
	Q_OBJECT

public:
	Browser(QWidget *parent = 0);

	private slots:
	void SlotEnter();       // For Enter in LineEdit
	void SetUrl(const QUrl &url); // For clicked URL

private:
		std::unique_ptr<Ui::BrowserClass> ui_;
};



