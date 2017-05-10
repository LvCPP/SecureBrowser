#pragma once
#include "LoginDynLib.h"
#include <QDialog>

namespace BrowserLogin
{

class LoginAppPrivate;
class LoginApp : public QDialog
{
	Q_OBJECT
public:
	explicit LOGIN_API LoginApp(QWidget* parent = Q_NULLPTR);
	virtual LOGIN_API ~LoginApp(); 
protected:
	LoginAppPrivate* const d_ptr;
private:
	Q_PRIVATE_SLOT(d_func(), void OnPushButtonLoginClick())
	Q_PRIVATE_SLOT(d_func(), void PhotoAccepted())
	Q_DECLARE_PRIVATE(LoginApp)
};

}