#pragma once

#include "LoginApp2.h"

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

private slots:
	bool CheckLogin();
};
}