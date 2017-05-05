#pragma once
#include"LoginApp.hpp"
#include <QDialog>
namespace Ui {class LoginDialog;}

class LoginDialog : public QDialog {
	Q_OBJECT

public:
	LoginDialog(QDialog * parent = Q_NULLPTR);
	~LoginDialog();

private:
	BrowserLogin::LoginApp* login_;
	Ui::LoginDialog *ui;
};
