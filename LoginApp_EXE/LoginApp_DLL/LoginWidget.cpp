#include <qmessagebox.h>
#include "LoginWidget.hpp"
using namespace BrowserLogin;

LoginWidget::LoginWidget(QWidget * parent) : 
	QWidget(parent)
	,ui_(new Ui::LoginWidgetClass())
{
	SetupWindow();
	connect(ui_->line_edit_username, &QLineEdit::textChanged, this, &LoginWidget::UsernameChanged);
	connect(ui_->line_edit_password, &QLineEdit::textChanged, this, &LoginWidget::UsernameChanged);
	connect(ui_->push_btn_login, &QPushButton::clicked, this, &LoginWidget::LoginButtonClicked);
}

void LoginWidget::UsernameChanged()
{
	bool is_login_activated = (!ui_->line_edit_username->text().isEmpty()) 
		&& (!ui_->line_edit_password->text().isEmpty());
	ui_->push_btn_login->setEnabled(is_login_activated);
}

void LoginWidget::SetupWindow()// TBD(interface)
{
	ui_->setupUi(this);
	setWindowTitle("Login");
	QPixmap logo(":/icons/Icons/share-image.png");
	int width = ui_->label_SoftServeLogo->width();
	int height = ui_->label_SoftServeLogo->height();
	ui_->label_SoftServeLogo->setPixmap(logo.scaled(width, height, Qt::KeepAspectRatio));
	ui_->push_btn_login->setEnabled(false);
	ui_->push_button_start_test->setVisible(false);
}

bool LoginWidget::IsUsernameAndPasswordValid()// TBD
{
	QString username = ui_->line_edit_username->text();
	QString password = ui_->line_edit_password->text();
	if (username == "12345" && password == "12345")
		return true;
	return false;
}

void LoginWidget::ResetPassword()
{
	ui_->line_edit_password->clear();
}
