#include "LoginCamera.hpp"
#include "ui_logincamera.h"

LoginCamera::LoginCamera(QWidget *parent) :
	QWidget(parent),
	ui_(std::make_unique<Ui::LoginCamera>())
{
	SetupWindow();

	connect(ui_->push_button_make_another_photo, &QPushButton::clicked, this, &LoginCamera::MakePhoto);
}

void LoginCamera::MakePhoto()
{
	// TBD
	QImage photo(":/Icons/Resources/share-image.png");
	QPixmap picture = QPixmap::fromImage(photo);
	int width = ui_->label_photo->width();
	int height = ui_->label_photo->height();
	ui_->label_photo->setPixmap(picture.scaled(width, height, Qt::KeepAspectRatio));
	ui_->push_button_accept_photo->setEnabled(true);
	ui_->push_button_make_another_photo->setText("New Photo");
}

QPushButton* LoginCamera::getAcceptPhotoButton()
{
	return ui_->push_button_accept_photo;
}

void LoginCamera::SetupWindow()
{
	//TBD(interface)
	ui_->setupUi(this);
	ui_->push_button_accept_photo->setEnabled(false);
}
