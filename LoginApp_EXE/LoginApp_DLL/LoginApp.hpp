#pragma once
#include <QDialog>
#include "LoginDynLib.h"

namespace BrowserLogin
{

class LoginAppPrivate;
class LoginApp : public QDialog 
{
	Q_OBJECT
public:
	explicit LOGIN_API LoginApp(QWidget * parent = Q_NULLPTR);
	virtual ~LoginApp(); //for potential further implementation
protected:
	LoginAppPrivate* const d_ptr;
private:
	Q_PRIVATE_SLOT(d_func(), void _q_OnPushButtonLoginClick())
	Q_PRIVATE_SLOT(d_func(), void _q_PhotoAccepted())
	Q_DECLARE_PRIVATE(LoginApp)
};

}