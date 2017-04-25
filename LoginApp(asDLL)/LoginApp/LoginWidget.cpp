#include <qmessagebox.h>
#include "LoginWidget.hpp"

LoginWidget::LoginWidget(QWidget * parent) : QWidget(parent), ui_(std::make_unique<Ui::LoginWidget>())
{
	SetupWindow();
	connect(ui_->line_edit_username, &QLineEdit::textChanged, this, &LoginWidget::UsernameChanged);
	connect(ui_->line_edit_password, &QLineEdit::textChanged, this, &LoginWidget::UsernameChanged);
}

void LoginWidget::UsernameChanged()
{
	bool is_login_activated = (!ui_->line_edit_username->text().isEmpty()) && (!ui_->line_edit_password->text().isEmpty());
	ui_->push_btn_login->setEnabled(is_login_activated);
}

void LoginWidget::SetupWindow()// TBD(interface)
{
	ui_->setupUi(this);
	setWindowTitle("Login");
	QPixmap logo(":/Icons/Resources/share-image.png");
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

QPushButton* LoginWidget::getLoginButton()
{
	return ui_->push_btn_login; 
}

void LoginWidget::CleanPassword()
{
	ui_->line_edit_password->clear(); 
}
