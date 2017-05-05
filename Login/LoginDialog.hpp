#pragma once
#include"LoginApp.hpp"
#include"ui_LoginDialog.h"
#include <QDialog>

namespace BrowserLogin
{

class LoginDialog : public QDialog {
	Q_OBJECT

public:
	LoginDialog(QDialog * parent = Q_NULLPTR);
private:
	BrowserLogin::LoginApp* login_;
	QScopedPointer<Ui::LoginDialog> ui_;
};

}