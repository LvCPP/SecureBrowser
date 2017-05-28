#pragma once

#include <QDialog>
#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QMdiArea>
#include <QSettings>
#include <QDebug>

#include "WelcomePage.h"
#include "LoginPage.h"
#include "MakePhotoPage.h"
#include "LastPage.h"

#include "LoginUtils.h"

//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
#include <iostream>
#include <fstream>

#include <string>

//#include <cpprest\json.h>
//
//using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
//using namespace web::http;                  // Common HTTP functionality
//using namespace web::http::client;          // HTTP client features
//using namespace concurrency::streams;       // Asynchronous streams

namespace Login
{

class LoginApp2 : public QWizard
{
	Q_OBJECT
public:
	LOGIN2APP 
		LoginApp2(QWidget *parent = Q_NULLPTR);
	LOGIN2APP 
		~LoginApp2();
	void CreateWindow();
	void CreateWizardButtonsLayout();
	void SetPageSequence();
	void SetFirstRunSetting();
	bool FirstRun();
	void RemoveFirstRunSetting();
	enum
	{
		WELCOME_PAGE
		, LOGIN_PAGE
		, MAKE_PHOTO_PAGE
		, MAKE_PHOTO_ID_PAGE
		, LAST_PAGE
	};
private:
	QString wnd_title;
	int wnd_width;
	int wnd_height;
	QList<QWizard::WizardButton> layout;
};



}
