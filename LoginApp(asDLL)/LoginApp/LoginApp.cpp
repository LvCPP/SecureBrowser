#include<qstackedwidget.h>
#include<qmessagebox.h>
#include "LoginApp.h"
#include "LoginWidget.hpp"
#include "LoginCamera.hpp"

const size_t WINDOWHEIGHT = 470;
const size_t WINDOWWIDTH = 400;

LoginApp::LoginApp(QStackedWidget *parent)
	: QStackedWidget(parent),
    login_(std::make_unique<LoginWidget>(this)),
    camera_login_(std::make_unique<LoginCamera>(this))
{

	SetupWindow();//TBD(interface)

	connect(login_->getLoginButton(), &QPushButton::clicked, this, &LoginApp::OnPushButtonLoginClick);
	connect(camera_login_->getAcceptPhotoButton(), &QPushButton::clicked, this, &LoginApp::PhotoAccepted);

	addWidget(login_.get());
	addWidget(camera_login_.get());

	setCurrentWidget(login_.get());

}

void LoginApp::SetupWindow()
{
	setMinimumSize(WINDOWHEIGHT, WINDOWWIDTH);
	setMaximumSize(WINDOWHEIGHT, WINDOWWIDTH);
}

void LoginApp::AskCameraAccess()
{
	QString message = tr("You have successfully completed login. \nTo start test take your photo.");
	QMessageBox box_camera_confirm(QMessageBox::Information, tr("Confirm login"), message);
	QIcon title(":/Icons/Resources/warning.png");
	box_camera_confirm.setWindowIcon(title);
	box_camera_confirm.addButton(tr("&Turn on camera"), QMessageBox::AcceptRole);
	box_camera_confirm.addButton(QMessageBox::Abort);

	int Action = box_camera_confirm.exec();

	switch (Action)
	{
	case QMessageBox::AcceptRole:
		setCurrentWidget(camera_login_.get());
		break;
	case QMessageBox::Abort:
		close();
		break;
	default:
		close();
		break;
	}
}

void LoginApp::OnPushButtonLoginClick()
{
	if (login_->IsUsernameAndPasswordValid())
	{
		AskCameraAccess();
	}
	else
	{
	    QMessageBox::warning(this, "Login", tr("Username or password are incorrect, try again"));
		login_->CleanPassword();
	}
}

void LoginApp::PhotoAccepted()
{
	SendImage();
	login_passed_ = true;
	close();
}

void LoginApp::SendImage()
{
	//TBD
}


