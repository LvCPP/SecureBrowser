#include "LoginCamera.hpp"
#include "ui_logincamera.h"
using namespace BrowserLogin;

LoginCamera::LoginCamera(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::LoginCamera())
{
	SetupWindow();
	connect(ui_->push_button_make_another_photo, &QPushButton::clicked, this, &LoginCamera::MakePhoto);
	connect(ui_->push_button_accept_photo, &QPushButton::clicked, this, &LoginCamera::AcceptPhotoButtonClicked);
}

void LoginCamera::MakePhoto()
{
	// TBD
	QImage photo(":/icons/Icons/share-image.png");
	QPixmap picture = QPixmap::fromImage(photo);
	int width = ui_->label_photo->width();
	int height = ui_->label_photo->height();
	ui_->label_photo->setPixmap(picture.scaled(width, height, Qt::KeepAspectRatio));
	ui_->push_button_accept_photo->setEnabled(true);
	ui_->push_button_make_another_photo->setText("New Photo");
}

void LoginCamera::SetupWindow()
{
	//TBD(interface)
	ui_->setupUi(this);
	ui_->push_button_accept_photo->setEnabled(false);
}