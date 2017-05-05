#include "LoginDialog.hpp"
#include "ui_logindialog.h"
using namespace BrowserLogin;

LoginDialog::LoginDialog(QDialog * parent) : 
	QDialog(parent)
	,login_(new LoginApp(this))
{
	connect(login_, &LoginApp::AcceptPhotoClicked, [this] {this->reject(); });
	connect(login_, &LoginApp::RejectClicked, [this] {this->reject(); });

	ui = new Ui::LoginDialog();
	ui->setupUi(this); 

}

LoginDialog::~LoginDialog() {
	delete ui;
}
