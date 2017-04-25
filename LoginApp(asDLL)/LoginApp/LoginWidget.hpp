#pragma once
#include <QWidget>
#include <memory>
#include "ui_LoginWidget.h"

class LoginWidget : public QWidget {
	Q_OBJECT

public:

	explicit LoginWidget(QWidget * parent = Q_NULLPTR);
	bool IsUsernameAndPasswordValid(); // TBD
	QPushButton* getLoginButton();
	void CleanPassword();

	private slots:
	void UsernameChanged();

private:
	void SetupWindow();// TBD(interface)
	std::unique_ptr<Ui::LoginWidget> ui_;
};
