#include "MakePhotoPage.h"

#include "WebCamController.h"
#include <QFont>
#include <QString>
#include <QProgressBar>
#include <QImage>
#include <QPixmap>

#include <vector>
#include <string>

using namespace Utils;
using namespace CameraInspector;
using namespace Login;

static const QString white_color = "background-color: rgb(255, 255, 255);";
static const QString gray_color = "background-color: rgb(225, 225, 225);";
static const QFont arial_12("Arial", 12);

MakePhotoPage::MakePhotoPage(QWidget *parent)
	: QWizardPage(parent)
	, is_enabled_(false)
	, is_update_(true)
{
	CreateCameraSelectLabel();
	CreateCameraSelectComboBox();
	CreateCameraArea();
	CreateButtons();

	connect(make_photo_button_, SIGNAL(clicked()), this, SLOT(MakePhoto()));
	connect(camera_select_combobox_, SIGNAL(activated(int)), this, SLOT(OnCameraChoose(int)));
	connect(accept_button_, SIGNAL(clicked()), this, SLOT(CreateProgressBar()));
}

MakePhotoPage::~MakePhotoPage()
{
}

int MakePhotoPage::nextId() const
{
	is_enabled_ = false;
	if (camera_select_combobox_->currentText() == "")
		return LoginApp2::MAKE_PHOTO_PAGE;
	else
		return LoginApp2::LAST_PAGE;
}

void MakePhotoPage::CreateCameraSelectLabel()
{
	QLabel* camera_select_label = new QLabel(this);
	camera_select_label->setGeometry(QRect(230, 40, 350, 22));
	camera_select_label->setFont(arial_12);
	camera_select_label->setText("Please select your web-camera for face detecting:");
}

void MakePhotoPage::CreateCameraSelectComboBox()
{
	An<WebCamController> wcc;
	std::vector<std::string> cam_names = wcc->ListNamesOfCameras();
	
	//Model-view QT to be done
	QLabel* camera_select_label = new QLabel(this);
	camera_select_combobox_ = new QComboBox(this);
	camera_select_combobox_->setGeometry(QRect(240, 70, 330, 23));
	camera_select_combobox_->setFont(arial_12);
	
	for (std::string name : cam_names)
		camera_list_ << QString::fromStdString(name);

	camera_select_combobox_->addItems(camera_list_);
	camera_select_combobox_->setStyleSheet(white_color);
}

void MakePhotoPage::CreateCameraArea()
{
	image_label_ = new QLabel(this);
	image_label_->setGeometry(190, 110, 440, 330);
	image_label_->show();
}

void MakePhotoPage::CreateButtons()
{
	QFont button_font;
	button_font.setFamily(QStringLiteral("Arial"));
	button_font.setPointSize(10);
	
	make_photo_button_ = new QPushButton(this);
	make_photo_button_->setGeometry(QRect(210, 470, 90, 30));
	make_photo_button_->setFont(button_font);
	make_photo_button_->setStyleSheet(gray_color);
	make_photo_button_->setText("Make photo");

	accept_button_ = new QPushButton(this);
	accept_button_->setGeometry(QRect(360, 470, 90, 30));
	accept_button_->setFont(button_font);
	accept_button_->setStyleSheet(gray_color);
	accept_button_->setText("Accept");
	accept_button_->setDisabled(true);

	decline_button_ = new QPushButton(this);
	decline_button_->setGeometry(QRect(500, 470, 90, 30));
	decline_button_->setFont(button_font);
	decline_button_->setStyleSheet(gray_color);
	decline_button_->setText("Decline");
	decline_button_->setDisabled(true);
}

void MakePhotoPage::OnCameraChoose(int id)
{
	An<WebCamController>()->ActivateCamera(An<WebCamController>()->GetCameras().at(0));
}

void MakePhotoPage::CreateProgressBar()
{
	/*QProgressBar* progress_bar = new QProgressBar;
	progress_bar->setRange(0, 5);
	progress_bar->setMinimumWidth(20);
	progress_bar->setAlignment(Qt::AlignBottom);*/
}

void MakePhotoPage::CameraThread()
{
	while (is_enabled_)
	{
		if (is_update_)
		{
			Frame f_img = An<WebCamController>()->GetActiveCamera().GetFrame();

			QImage img(640, 480, QImage::Format_RGBA8888);
			for (int y = 0; y < 480; ++y)
			{
				for (int x = 0; x < 640; ++x)
				{
					int index(y * 640 + x);
					img.setPixel(x, y, reinterpret_cast<int*>(f_img.GetData())[index]);
				}
			}
			img = img.scaled(430, 330, Qt::KeepAspectRatio);

			image_label_->setPixmap(QPixmap::fromImage(img));
		}
	}
}

void MakePhotoPage::InitCamera()
{
	if (is_update_)
	{
		An<WebCamController>()->ActivateCamera(An<WebCamController>()->GetCameras().at(0));
		is_enabled_ = true;
		worker_ = std::thread(&MakePhotoPage::CameraThread, this);
	}
}

void MakePhotoPage::MakePhoto()
{
	decline_button_->setEnabled(true);
	accept_button_->setEnabled(true);
	is_update_ = false;
}

