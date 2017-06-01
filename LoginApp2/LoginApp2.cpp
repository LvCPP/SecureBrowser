#include "LoginApp2.h"

#include <QList>
#include <QString>
#include <QWizard>
#include <QIcon>

using namespace Login;

static const QString wnd_title = "SecureBrowser authentication process";
static const int wnd_width = 640;
static const int wnd_height = 480;

static const QString reg_path = "HKEY_CURRENT_USER\\Software\\SoftServe\\SecureBrowser";
static const QString reg_group_name = "Run";
static const QString reg_value_name = "FirstRun";

LoginApp2::LoginApp2(QWidget *parent)
	: QWizard(parent)
{
	CreateMyWindow();
	CreateWizardButtonsLayout();
	SetPageSequence();
}

void LoginApp2::CreateMyWindow()
{
	setWindowTitle(wnd_title);
	
	setFixedSize(wnd_width, wnd_height);

	setWindowFlags(Qt::Window);
	setOptions(QWizard::NoCancelButtonOnLastPage);

	setWizardStyle(QWizard::ModernStyle);

	QIcon winIcon(":Resources/sb.ico");
	setWindowIcon(winIcon);
}

void LoginApp2::CreateWizardButtonsLayout()
{
	QList<QWizard::WizardButton> layout;
	layout << QWizard::Stretch << QWizard::NextButton << QWizard::CancelButton << QWizard::FinishButton;
	
	setButtonLayout(layout);
}

void LoginApp2::SetPageSequence()
{
	setPage(WELCOME_PAGE, new WelcomePage);
	setPage(LOGIN_PAGE, new LoginPage);
	setPage(MAKE_PHOTO_PAGE, new MakePhotoPage);
	setPage(LAST_PAGE, new LastPage);
	
	setStartId(WELCOME_PAGE);
	
	SetFirstRunSetting();
	//RemoveFirstRunSetting(); // comments should be deleted if you want to show the welcome page
}

void LoginApp2::SetFirstRunSetting()
{
	QSettings setting(reg_path);
	setting.setDefaultFormat(QSettings::Registry64Format); 
	// Windows only:
	// Explicitly access the 64-bit system registry from a 32-bit application running on 64-bit Windows.
	// On 32-bit Windows or from a 64-bit application on 64-bit Windows, this works the same as
	// specifying NativeFormat. Was added in Qt 5.7.
		
	setting.beginGroup(reg_group_name);
	bool first_run = false;
	setting.setValue(reg_value_name, first_run);
	setting.endGroup();
}

bool LoginApp2::FirstRun()
{
	QSettings setting(reg_path);

	setting.setDefaultFormat(QSettings::Registry64Format);
	setting.beginGroup(reg_group_name);
	QStringList keys = setting.childKeys();
	if (!keys.contains(reg_value_name, Qt::CaseInsensitive))
		return true;
	else
		return false;
	setting.endGroup();
}

void LoginApp2::RemoveFirstRunSetting()
{
	QSettings setting(reg_path);

	setting.setDefaultFormat(QSettings::Registry64Format);
	setting.beginGroup(reg_group_name);
	setting.remove(reg_value_name);
	setting.endGroup();
}

