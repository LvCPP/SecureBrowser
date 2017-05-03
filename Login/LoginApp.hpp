#pragma once
#include"LoginDynLib.h"
#include<QtWidgets/QWidget>
#include<QObject>
#include<qstackedwidget.h>

namespace BrowserLogin
{
class LoginAppPrivate;
class LoginApp : public QStackedWidget
{
	Q_OBJECT
public:
	explicit LOGIN_API LoginApp(QStackedWidget* parent = Q_NULLPTR);
protected:
	LoginAppPrivate* const d_ptr; // d-pointer
	LoginApp(LoginAppPrivate &&another_d_ptr, QStackedWidget *parent); //TBD
private:
	Q_PRIVATE_SLOT(d_func(), void _q_OnPushButtonLoginClick())
	Q_PRIVATE_SLOT(d_func(), void _q_PhotoAccepted())
	Q_DECLARE_PRIVATE(LoginApp)
};
}

