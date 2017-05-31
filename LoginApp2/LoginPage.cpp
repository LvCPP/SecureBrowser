#include "LoginPage.h"

#include <QString>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <string>

using namespace Login;


static const QFont arial_12("Arial", 12);

static const QString white_color = "background-color: rgb(255, 255, 255);";
static const QString gray_color = "background-color: rgb(225, 225, 225);";

LoginPage::LoginPage(QWidget* parent)
	: QWizardPage(parent)
{
	CreateLoginPageBackground();

	CreateTopLabel();
	CreateUsernameLabel();
	CreateUsernameLineedit();
	CreatePasswordLabel();
	CreatePasswordLineEdit();
	CreateAgreeCheckBox();
	CreateAgreeLabel();

	CreateLoginButton();

	login_checked_ = false;

	connect(login_button_, SIGNAL(clicked()), this, SLOT(CheckLogin()));
	connect(agree_checkbox_, SIGNAL(toggled(bool)), login_button_, SLOT(setEnabled(bool)));
}

LoginPage::~LoginPage()
{
}

void LoginPage::CreateLoginPageBackground()
{
	setStyleSheet(white_color);
}

void LoginPage::CreateTopLabel()
{
	QLabel* top_label = new QLabel(this);
	top_label->setText("You are invited to take the test as one of the stages\n to be "
		"enrolled in SoftServe IT Academy.\n\n"
		"Please input your credentials:");
	top_label->setGeometry(QRect(95, 45, 450, 50));
	top_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	top_label->setFont(arial_12);
	top_label->setWordWrap(true);
}

void LoginPage::CreateUsernameLabel()
{
	QLabel* username_label = new QLabel(this);
	username_label->setGeometry(QRect(185, 120, 80, 20));
	username_label->setAlignment(Qt::AlignRight);
	username_label->setFont(arial_12);
	username_label->setText("Username*");
}

void LoginPage::CreateUsernameLineedit()
{
	username_lineedit_ = new QLineEdit(this);
	username_lineedit_->setGeometry(QRect(300, 120, 150, 20));
	username_lineedit_->setFont(arial_12);
	registerField("Username*", username_lineedit_);
}

void LoginPage::CreatePasswordLabel()
{
	QLabel* password_label = new QLabel(this);
	password_label->setGeometry(QRect(185, 160, 80, 20));
	password_label->setAlignment(Qt::AlignRight);
	password_label->setFont(arial_12);
	password_label->setText("Password*");
}

void LoginPage::CreatePasswordLineEdit()
{
	password_lineedit_ = new QLineEdit(this);
	password_lineedit_->setGeometry(QRect(300, 160, 150, 20));
	password_lineedit_->setFont(arial_12);
	password_lineedit_->setEchoMode(QLineEdit::Password);
	registerField("Password*", password_lineedit_);
}

void LoginPage::CreateAgreeCheckBox()
{
	agree_checkbox_ = new QCheckBox(this);
	agree_checkbox_->setGeometry(185, 200, 30, 25);
	registerField("agree_checkbox_*", agree_checkbox_);
}

void LoginPage::CreateAgreeLabel()
{
	QLabel* agree_label = new QLabel(this);
	agree_label->setGeometry(QRect(215, 205, 240, 25));
	agree_label->setAlignment(Qt::AlignLeft);
	agree_label->setFont(arial_12);
	agree_label->setText("<html><head / ><body><p><span style = \" font-size:12pt;\">I agree with "
		"</span><a href=\"https://drive.google.com/open?id=0B9Xa2M9s3StoOFNXYXQ2QWZPZ28\"><span style=\" font-size:12pt;"
		"text-decoration: underline; color:#0000ff;\">Rules and Agreements</span></a></p></body></html>");
	agree_label->setOpenExternalLinks(true);
}

void LoginPage::CreateLoginButton()
{
	login_button_ = new QPushButton(this);
	login_button_->setGeometry(QRect(280, 260, 80, 25));
	login_button_->setText("Login");
	QFont button_font;
	button_font.setFamily(QStringLiteral("Arial"));
	button_font.setPointSize(10);
	login_button_->setDisabled(true);
	login_button_->setFont(button_font);
	login_button_->setStyleSheet(gray_color);
}

bool LoginPage::CheckLogin()
{
	QString  username = username_lineedit_->text();
	QString password = password_lineedit_->text();

	if (username == "12345" && password == "12345")

	{
		login_checked_ = true;
		QMessageBox::information(this, "Login", "User found");
		return true;
	}
	else
	{
		QMessageBox::warning(this, "Login", "Not correct. "
			"Please provide correct username and password");
		return false;
	}
}

int LoginPage::nextId() const
{
	bool login_button_enabled = login_button_->isEnabled();
	if (login_checked_ && login_button_enabled)
	{
		return LoginApp2::MAKE_PHOTO_PAGE;
	}
	else
	{
		return LoginApp2::LOGIN_PAGE;
	}
}



	

	





