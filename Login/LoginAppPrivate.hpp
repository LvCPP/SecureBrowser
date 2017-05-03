#pragma once
#include"LoginApp.hpp"
#include<QObject>
#include<memory>

namespace BrowserLogin
{
class LoginWidget;
class LoginCamera;
class LoginAppPrivate : QObject
{
	Q_DISABLE_COPY(LoginAppPrivate)
	Q_DECLARE_PUBLIC(LoginApp)
public:
	explicit LoginAppPrivate(QObject* parent = Q_NULLPTR);
	virtual ~LoginAppPrivate() = default;
	LoginApp* q_ptr; //q-pointer

	void _q_PhotoAccepted(); //_q_ is a rule for naming private slots
	void _q_OnPushButtonLoginClick();

	void SetupWindow(); //TBD(interface)
	void AskCameraAccess();
	void SendImage(); // TBD
	bool login_passed_ = false;
	std::unique_ptr<LoginWidget> login_;
	std::unique_ptr<LoginCamera> camera_login_;
};
}
