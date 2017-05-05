#include "LoginDialog.hpp"
#include "ui_logindialog.h"
using namespace BrowserLogin;

LoginDialog::LoginDialog(QDialog * parent) : 
	QDialog(parent)
	,login_(new LoginApp(this))
	,ui_(new Ui::LoginDialog())
{
	connect(login_, &LoginApp::AcceptPhotoClicked, [this] {this->accept(); });
	connect(login_, &LoginApp::RejectClicked, [this] {this->reject(); });
	ui_->setupUi(this); 
}

