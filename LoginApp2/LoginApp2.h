#pragma once

#include "LoginUtils.h"

#include "WelcomePage.h"
#include "LoginPage.h"
#include "MakePhotoPage.h"
#include "LastPage.h"

#include <QDialog>
#include <QWizard>
#include <QWidget>
#include <QWizardPage>

#include <QSettings>
#include <QAbstractButton>
#include <QString>

//#include <QWizardPage>
//#include <QLabel>
//#include <QPushButton>
//#include <QLineEdit>
//#include <QComboBox>
//#include <QCheckBox>
//#include <QMessageBox>
//
//
//#include <QDebug>
//

//
//#include <iostream>
//#include <fstream>
//
//#include <string>

namespace Login
{

class LoginApp2 : public QWizard
{
	Q_OBJECT

public:
	LOGIN2APP LoginApp2(QWidget *parent = Q_NULLPTR);
	LOGIN2APP ~LoginApp2();

	enum
	{
		WELCOME_PAGE
		, LOGIN_PAGE
		, MAKE_PHOTO_PAGE
		, LAST_PAGE
	};

	void SetPageSequence();
	void SetFirstRunSetting();
	bool FirstRun();
	void RemoveFirstRunSetting();

private:
	void CreateMyWindow();
	void CreateWizardButtonsLayout();
};

}
