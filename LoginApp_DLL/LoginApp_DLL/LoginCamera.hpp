#pragma once
#include <QWidget>
#include <memory>
#include "ui_LoginCamera.h"
class QPushButton;

class LoginCamera : public QWidget {
	Q_OBJECT

public:

	explicit LoginCamera(QWidget *parent = Q_NULLPTR);
	QPushButton* GetAcceptPhotoButton() const;
private slots:
	void MakePhoto();// TBD

private:
	void SetupWindow(); // TBD(interface)
	std::unique_ptr<Ui::LoginCamera> ui_;
};
