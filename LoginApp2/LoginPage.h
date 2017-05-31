#pragma once

#include "LoginApp2.h"
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <functional>
#include <memory>

#include <iostream>
#include <iostream>
#include <sstream>

#include "HttpClientUtils.h"
#include "HttpClient.h"

namespace Login
{
class LoginPage : public QWizardPage
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = 0);
	~LoginPage();

	/*void LoginCheck();*/
	/*void MoodleAuthenticated();*/
		
	int nextId() const override;
	
private:
	void CreateLoginPageBackground();
	void CreateTopLabel();
	void CreateUsernameLabel();
	void CreateUsernameLineedit();
	void CreatePasswordLabel();
	void CreatePasswordLineEdit();
	void CreateAgreeCheckBox();
	void CreateAgreeLabel();
	void CreateLoginButton();

	QCheckBox* agree_checkbox_;
	QPushButton* login_button_;
	QLineEdit* username_lineedit_;
	QLineEdit* password_lineedit_;
	bool login_checked_;

private slots:
	bool CheckLogin();
};

}