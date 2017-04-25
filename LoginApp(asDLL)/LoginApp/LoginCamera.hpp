#pragma once
#include <QWidget>
#include <memory>
class QPushButton;
namespace Ui {class LoginCamera;}

class LoginCamera : public QWidget {
	Q_OBJECT

public:

	explicit LoginCamera(QWidget *parent = Q_NULLPTR);
	QPushButton* getAcceptPhotoButton();


	private slots:
	void MakePhoto();// TBD

private:
	void SetupWindow(); // TBD(interface)
	std::unique_ptr<Ui::LoginCamera> ui_;
};
