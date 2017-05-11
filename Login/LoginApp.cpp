#include "LoginApp.h"
#include "LoginAppPrivate.h"
#include "LoginWidget.h"
#include "LoginCamera.h"
#include <QMessageBox>
using namespace BrowserLogin;

LoginAppPrivate::LoginAppPrivate(): ui_(new Ui::LoginApp())
{
}

LoginApp::LoginApp(QWidget* parent)
	: QDialog(parent)
	, d_ptr(new LoginAppPrivate())
{
	Q_D(LoginApp);//for access to private class methods and variables from public class method 
	d->ui_->setupUi(this);
	d->q_ptr = this;
	d->SetupWidgets();
	connect(d->login_,
		&LoginWidget::LoginButtonClicked,
		[d] {d->OnPushButtonLoginClick(); });
	connect(d->camera_login_,
		&LoginCamera::AcceptPhotoButtonClicked,
		[d] {d->PhotoAccepted(); });
}

void LoginAppPrivate::SetupWidgets()
{
	login_ = new LoginWidget(ui_->stacked_widget);
	camera_login_ = new LoginCamera(ui_->stacked_widget);
	ui_->stacked_widget->addWidget(login_);
	ui_->stacked_widget->addWidget(camera_login_);
	ui_->stacked_widget->setCurrentWidget(login_);
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
		ui_->stacked_widget->setCurrentWidget(camera_login_);
		break;
	default:
		emit q->reject();
		break;
	}
}

void LoginAppPrivate::OnPushButtonLoginClick()
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

void LoginAppPrivate::PhotoAccepted()
{
	Q_Q(LoginApp);
	SendImage();
	emit q->accept();
}

void LoginAppPrivate::SendImage()
{
	//TBD
}

LoginApp::~LoginApp()
{
	delete d_ptr;
}

#include "moc_LoginApp.cpp" //needed to be included becouse moc, generated
//by LoginApp knows anything about LoginAppPrivate  