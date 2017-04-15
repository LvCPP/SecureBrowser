#pragma once

#include <QtWidgets/QWidget>
#include <qstackedwidget.h>
#include <memory>

class LoginWidget;
class LoginCamera;

class LoginApp : public QStackedWidget
{
	Q_OBJECT
public:
	explicit __declspec(dllexport) LoginApp(QStackedWidget *parent = Q_NULLPTR);
	bool LoginPassed() { return login_passed_; }

	private slots:
	void PhotoAccepted();
	void OnPushButtonLoginClick();

private:
	void SetupWindow(); //TBD(interface)
	void AskCameraAccess();
	void SendImage(); // TBD
	bool login_passed_ = false;
	std::unique_ptr<LoginWidget> login_;
	std::unique_ptr<LoginCamera> camera_login_;
};

