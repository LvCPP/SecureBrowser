#pragma once
#include"LoginApp.hpp"
#include<QObject>
#include<memory>

namespace BrowserLogin
{
class LoginWidget;
class LoginCamera;

class LoginAppPrivate
{
public:
	explicit LoginAppPrivate() = default;
	virtual ~LoginAppPrivate();

	void _q_PhotoAccepted(); //_q_ is a rule for naming private slots
	void _q_OnPushButtonLoginClick();

	void SetupWindow(); //TBD(interface)
	void AskCameraAccess();
	void SendImage(); // TBD
	LoginApp* q_ptr;
	LoginWidget* login_;
	LoginCamera* camera_login_;
	bool login_passed_ = false;
private:
	Q_DISABLE_COPY(LoginAppPrivate)
	Q_DECLARE_PUBLIC(LoginApp)

};

}
