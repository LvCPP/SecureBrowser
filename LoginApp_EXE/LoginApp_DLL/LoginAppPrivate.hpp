#pragma once
#include"ui_LoginApp.h"
#include<qstackedwidget.h>
#include<memory>

namespace BrowserLogin
{

class LoginWidget;
class LoginCamera;
class LoginAppPrivate
{
public:
	LoginAppPrivate();
	virtual ~LoginAppPrivate() = default; //for potential further implementation

	void _q_PhotoAccepted(); 
	void _q_OnPushButtonLoginClick();

	void SetupWidgets();
	void AskCameraAccess();
	void SendImage(); // TBD
    LoginApp* q_ptr;
	LoginWidget* login_;
	LoginCamera* camera_login_;
	QScopedPointer<Ui::LoginApp> ui_;
private:
	Q_DISABLE_COPY(LoginAppPrivate)
	Q_DECLARE_PUBLIC(LoginApp)
};

}
