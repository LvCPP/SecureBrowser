#pragma once

#include "LoginApp2.h"
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>

namespace Login
{
class LoginPage : public QWizardPage
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = 0);
	~LoginPage();

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

	void MoodleAuthenticated();
	
	bool login_checked_;
	QCheckBox* agree_checkbox_;
	QPushButton* login_button_;
	QLineEdit* username_lineedit_;
	QLineEdit* password_lineedit_;

private slots:
	bool CheckLogin();
};
}