#pragma once

#include "LoginApp2.h"
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <functional>

namespace Login
{
class LoginPage : public QWizardPage
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = 0);
	~LoginPage();

	int nextId() const override;

	void SetInitCameraFunction(const std::function<void()>& init_camera);
	
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

	std::function<void()> init_camera_;

private slots:
	bool CheckLogin();
};
}