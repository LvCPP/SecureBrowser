#pragma once
#include "ui_LoginWidget.h"
#include <QWidget>

namespace BrowserLogin
{

class LoginWidget : public QWidget 
{
	Q_OBJECT
public:
	explicit LoginWidget(QWidget* parent = Q_NULLPTR);
	bool IsUsernameAndPasswordValid(); // TBD
	void ResetPassword();
signals:
	void LoginButtonClicked();
private slots:
	void UsernameChanged();
private:
	void SetupWindow();// TBD(interface)
	QScopedPointer<Ui::LoginWidgetClass> ui_;
};

}