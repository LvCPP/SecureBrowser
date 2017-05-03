#include"LoginApp.hpp"
#include"LoginAppPrivate.hpp"
#include"LoginWidget.hpp"
#include"LoginCamera.hpp"
#include<qstackedwidget.h>
#include<qmessagebox.h>

using namespace BrowserLogin;

constexpr size_t WINDOWHEIGHT = 470;
constexpr size_t WINDOWWIDTH = 400;

LoginAppPrivate::LoginAppPrivate(QObject* parent) :QObject(parent)
{
}

LoginApp::LoginApp(LoginAppPrivate &&another_d_ptr, QStackedWidget *parent) : //TBD
	QStackedWidget(parent)
	,d_ptr(&another_d_ptr)
{
	Q_D(LoginApp);
	d->q_ptr = this;
}

LoginApp::LoginApp(QStackedWidget* parent) :
	QStackedWidget(parent)
	,d_ptr(new LoginAppPrivate())
{
	Q_D(LoginApp);//for access to private class methods and variables from public class method 
	d->q_ptr = this;
	d_ptr->login_ = std::make_unique<LoginWidget>(this);
	d_ptr->camera_login_ = std::make_unique<LoginCamera>(this);

	d_ptr->SetupWindow();
	connect(
		d_ptr->login_->GetLoginButton()
		, SIGNAL(clicked())
		, this
		, SLOT(_q_OnPushButtonLoginClick())
	);
	connect(
		d_ptr->camera_login_->GetAcceptPhotoButton()
		, SIGNAL(clicked())
		, this
		, SLOT(_q_PhotoAccepted())
	);

	addWidget(d_ptr->login_.get());
	addWidget(d_ptr->camera_login_.get());

	setCurrentWidget(d_ptr->login_.get());

}

void LoginAppPrivate::AskCameraAccess()
{
	Q_Q(LoginApp);//for access to public class from private class methods
	QString message = (tr("You have successfully completed login. \nTo start test take your photo.")); 
	QMessageBox box_camera_confirm(QMessageBox::Information, (tr("Confirm login")), message); 
	QIcon title(":/icons/Icons/warning.png");
	box_camera_confirm.setWindowIcon(title);
	box_camera_confirm.addButton((tr("&Turn on camera")), QMessageBox::AcceptRole); 
	box_camera_confirm.addButton(QMessageBox::Abort);

	int Action = box_camera_confirm.exec();

	switch (Action)
	{
	case QMessageBox::AcceptRole:
		q->setCurrentWidget(camera_login_.get());
		break;
	case QMessageBox::Abort:
		q->close();
		break;
	default:
		q->close();
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
		QMessageBox::warning(q, "Login", ("Username or password are incorrect, try again"));//add tr (q is like this)
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

void LoginAppPrivate::SendImage()
{
	//TBD
}

#include "moc_LoginApp.cpp" //needed to be included becouse moc, generated
//by LoginApp knows anything about LoginAppPrivate  
