#include "MakePhotoPage.h"
#include "WebCamController.h"
#include "../CameraInspector/FileSystemFrameSaver.h"

#include <QFont>
#include <QString>
#include <QImage>
#include <QPixmap>

#include <vector>
#include <string>
#include <functional>

using namespace Utils;
using namespace CameraInspector;
using namespace Login;
using namespace std;

static const QString white_color = "background-color: rgb(255, 255, 255);";
static const QString gray_color = "background-color: rgb(225, 225, 225);";
static const QFont arial_12("Arial", 12);

MakePhotoPage::MakePhotoPage(QWidget *parent)
	: QWizardPage(parent)
	, is_enabled_(true)
	, is_update_(true)
	, photo_made_(false)
{
	CreateCameraSelectLabel();
	CreateCameraSelectComboBox();
	CreateCameraArea();
	CreateButtons();

	connect(make_photo_button_, SIGNAL(clicked()), this, SLOT(MakePhoto()));
	connect(camera_select_combobox_, SIGNAL(activated(int)), this, SLOT(OnCameraChoose(int)));
	connect(decline_button_, SIGNAL(clicked()), this, SLOT(DeclineButtonClicked()));
	connect(accept_button_, SIGNAL(clicked()), this, SLOT(AcceptButtonClicked()));
}

MakePhotoPage::~MakePhotoPage()
{
}

int MakePhotoPage::nextId() const
{
	if (camera_select_combobox_->currentText() == "")
		return LoginApp2::MAKE_PHOTO_PAGE;
	else if(photo_made_)
		return LoginApp2::LAST_PAGE;
}

void MakePhotoPage::initializePage()
{
	InitCamera();
}

void MakePhotoPage::CreateCameraSelectLabel()
{
	QLabel* camera_select_label = new QLabel(this);
	camera_select_label->setGeometry(QRect(120, 10, 460, 20));
	camera_select_label->setFont(arial_12);
	camera_select_label->setText("Please select your web-camera for face and ID detecting:");
}

void MakePhotoPage::CreateCameraSelectComboBox()
{
	QLabel* camera_select_label = new QLabel(this);
	camera_select_combobox_ = new QComboBox(this);
	camera_select_combobox_->setGeometry(QRect(90, 40, 460, 25));
	camera_select_combobox_->setFont(arial_12);

	RefreshComboBox();
	
	camera_select_combobox_->setStyleSheet(white_color);
}

void MakePhotoPage::CreateCameraArea()
{
	image_label_ = new QLabel(this);
	image_label_->setGeometry(120, 70, 400, 300);
	image_label_->show();
}

void MakePhotoPage::CreateButtons()
{
	QFont button_font;
	button_font.setFamily(QStringLiteral("Arial"));
	button_font.setPointSize(10);
	
	make_photo_button_ = new QPushButton(this);
	make_photo_button_->setGeometry(QRect(120, 390, 80, 25));
	make_photo_button_->setFont(button_font);
	make_photo_button_->setStyleSheet(gray_color);
	make_photo_button_->setText("Make photo");

	accept_button_ = new QPushButton(this);
	accept_button_->setGeometry(QRect(280, 390, 80, 25));
	accept_button_->setFont(button_font);
	accept_button_->setStyleSheet(gray_color);
	accept_button_->setText("Accept");
	accept_button_->setDisabled(true);

	decline_button_ = new QPushButton(this);
	decline_button_->setGeometry(QRect(440, 390, 80, 25));
	decline_button_->setFont(button_font);
	decline_button_->setStyleSheet(gray_color);
	decline_button_->setText("Decline");
	decline_button_->setDisabled(true);
}

void MakePhotoPage::OnCameraChoose(int id)
{
	An<WebCamController>()->ActivateCamera(An<WebCamController>()->GetCameras().at(id));
}

void MakePhotoPage::CameraThread()
{
	while (is_enabled_)
	{
		if (is_update_)
		{
			id_frame_ = An<WebCamController>()->GetActiveCamera().GetFrame();

			QImage img(640, 480, QImage::Format_RGB32);
			for (int y = 0; y < 480; ++y)
			{
				for (int x = 0; x < 640; ++x)
				{
					int index(y * 640 + x);
					img.setPixel(x, y, reinterpret_cast<int*>(id_frame_.GetData())[index]);
				}
			}
			img = img.scaled(400, 300, Qt::KeepAspectRatio);

			image_label_->setPixmap(QPixmap::fromImage(img));
		}
	}
}

void MakePhotoPage::RefreshComboBox()
{
	An<WebCamController> wcc;
	std::vector<std::string> cam_names = wcc->ListNamesOfCameras();

	camera_list_.clear();
	camera_select_combobox_->clear();
	for (std::string name : cam_names)
		camera_list_ << QString::fromStdString(name);

	camera_select_combobox_->addItems(camera_list_);
}

void MakePhotoPage::InitCamera()
{
	An<WebCamController> wcc;
	wcc->ActivateCamera(wcc->GetCameras().at(0));
	wcc->SetRefreshCallback(std::bind(&MakePhotoPage::RefreshComboBox, this));
	is_enabled_ = true;
	worker_ = std::thread(&MakePhotoPage::CameraThread, this);
}

void MakePhotoPage::MakePhoto()
{
	is_update_ = false;
	decline_button_->setEnabled(true);
	accept_button_->setEnabled(true);
	make_photo_button_->setDisabled(true);
}

void MakePhotoPage::DeclineButtonClicked()
{
	make_photo_button_->setEnabled(true);
	accept_button_->setDisabled(true);
	decline_button_->setDisabled(true);
	
	is_update_ = true;
}

void Login::MakePhotoPage::AcceptButtonClicked()
{
	accept_button_->setDisabled(true);
	decline_button_->setDisabled(true);
	FileSystemFrameSaver saver;
	saver.SetNameToSave("ID_photo");
	saver.Save(id_frame_);
	photo_made_ = true;
}

