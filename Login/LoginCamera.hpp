#pragma once
#include "ui_LoginCamera.h"
#include <QWidget>

class QPushButton;
namespace BrowserLogin
{

class LoginCamera : public QWidget 
{
	Q_OBJECT
public:
	explicit LoginCamera(QWidget* parent = Q_NULLPTR);
signals:
	void AcceptPhotoButtonClicked();
private slots:
	void MakePhoto();// TBD
private:
	void SetupWindow(); // TBD(interface)
	QScopedPointer<Ui::LoginCamera> ui_;
};

}