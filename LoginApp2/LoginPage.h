#pragma once
#include "LoginApp2.h"

//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
//#include <cpprest/json.h>
//
//#include <iostream>
//
//using namespace utility;
//using namespace web;
//using namespace web::http;
//using namespace web::http::client;
//using namespace concurrency::streams;

using namespace std;

namespace Login
{
class LoginPage : public QWizardPage
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = 0);
	~LoginPage();

	int nextId() const override;
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

		
private:
	QString white_color;
	int x;
	int y;
	int width;
	int height;
	QLabel* top_label;
	QLabel* username_label;
	QLineEdit* username_lineedit;
	QLabel* password_label;
	QLineEdit* password_lineedit;
	QPushButton* login_button;
	QCheckBox* agree_checkbox;
	QLabel* agree_label;
	bool login_checked;

private slots:
	bool CheckLogin();
};
}