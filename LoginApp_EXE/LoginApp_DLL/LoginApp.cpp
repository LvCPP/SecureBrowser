#include"LoginApp.hpp"
#include"LoginAppPrivate.hpp"
#include"LoginWidget.hpp"
#include"LoginCamera.hpp"
#include<qstackedwidget.h>
#include<qmessagebox.h>
using namespace BrowserLogin;

namespace
{

constexpr size_t WINDOWHEIGHT = 470;
constexpr size_t WINDOWWIDTH = 400;

}

LoginApp::LoginApp(QWidget* parent) :
	QStackedWidget(parent)
	, d_ptr(new LoginAppPrivate())
{
	Q_D(LoginApp);//for access to private class methods and variables from public class method 
	d->q_ptr = this;
	d->SetupWindow();
	d->login_ = new LoginWidget(this);
	d->camera_login_ = new LoginCamera(this);
	connect(d->login_
		, &LoginWidget::LoginButtonClicked
		, [d] {d->_q_OnPushButtonLoginClick(); });
	connect(d->camera_login_
		, &LoginCamera::AcceptPhotoButtonClicked
		, [d] {d->_q_PhotoAccepted(); });
	connect(d->camera_login_, &LoginCamera::AcceptPhotoButtonClicked, this, &LoginApp::AcceptPhotoClicked);
    addWidget(d->login_);
	addWidget(d->camera_login_);
	setCurrentWidget(d->login_);
}

void LoginAppPrivate::AskCameraAccess()
{
	Q_Q(LoginApp);//for access to public class from private class methods
	QString message = ("You have successfully completed login. \nTo start test take your photo.");
	QMessageBox box_camera_confirm(QMessageBox::Information, "Confirm login", message);
	QIcon title(":/icons/Icons/warning.png");
	box_camera_confirm.setWindowIcon(title);
	box_camera_confirm.addButton("&Turn on camera", QMessageBox::AcceptRole);
	box_camera_confirm.addButton(QMessageBox::Abort);

	int action = box_camera_confirm.exec();
	switch (action)
	{
	case QMessageBox::AcceptRole:
		q->setCurrentWidget(camera_login_);
		break;
	default:
		emit q->RejectClicked();
		break;
	}
}

void LoginAppPrivate::_q_OnPushButtonLoginClick()
{
	Q_Q(LoginApp);
	if (login_->IsUsernameAndPasswordValid())
	{
		AskCameraAccess();
	}
	else
	{
		QMessageBox::warning(q, "Login", ("Username or password are incorrect, try again"));
		login_->ResetPassword();
	}
}

void LoginAppPrivate::SetupWindow() //TBD
{
	Q_Q(LoginApp);
	q->setMinimumSize(WINDOWHEIGHT, WINDOWWIDTH);
	q->setMaximumSize(WINDOWHEIGHT, WINDOWWIDTH);
}

void LoginAppPrivate::_q_PhotoAccepted()
{
	Q_Q(LoginApp);
	SendImage();
	login_passed_ = true;
	q->close();
}

LoginAppPrivate::~LoginAppPrivate()
{
	delete q_ptr;
}

LoginApp::~LoginApp()
{
	delete d_ptr;
}

void LoginAppPrivate::SendImage()
{
	//TBD
}

#include "moc_LoginApp.cpp" //needed to be included becouse moc, generated
//by LoginApp knows anything about LoginAppPrivate  