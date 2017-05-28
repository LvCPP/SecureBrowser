#include "MakePhotoPage.h"
#include "WebCamController.h"

#include <qbytearray.h>
#include <qstring.h>

#include <vector>
#include <string>

using namespace Utils;
using namespace CameraInspector;
using namespace Login;

MakePhotoPage::MakePhotoPage(QWidget *parent)
	: QWizardPage(parent)
	, is_enabled_(false)
	, is_update_(true)
{
	CreateCameraSelectLabel();
	CreateCameraSelectComboBox();
	CreateCameraArea();
	CreateButtons();

	connect(make_photo_button, SIGNAL(clicked()), this, SLOT(MakePhoto()));
	connect(camera_select_combobox, SIGNAL(activated(int)), this, SLOT(OnCameraChoose(int)));
}

MakePhotoPage::~MakePhotoPage()
{
}

int MakePhotoPage::nextId() const
{
	is_enabled_ = false;
	if (camera_select_combobox->currentText() == "")
		return LoginApp2::MAKE_PHOTO_PAGE;
	else
		return LoginApp2::LAST_PAGE;
}

void MakePhotoPage::CreateCameraSelectLabel()
{
	camera_select_label = new QLabel(this);
	x = 230;
	y = 40;
	width = 350;
	height = 22;
	camera_select_label->setGeometry(QRect(x, y, width, height));
	QFont arial_12("Arial", 12);
	camera_select_label->setFont(arial_12);
	camera_select_label->setText("Please select your web-camera for face detecting:");
}

void MakePhotoPage::CreateCameraSelectComboBox()
{
	An<WebCamController> wcc;
	std::vector<std::string> cam_names = wcc->ListNamesOfCameras();
	
	//Model-view QT
	camera_select_label = new QLabel(this);
	white_color = "background-color: rgb(255, 255, 255);";
	camera_select_combobox = new QComboBox(this);
	x = 240;
	y = 70;
	width = 330;
	height = 23;
	camera_select_combobox->setGeometry(QRect(x, y, width, height));
	QFont arial_12("Arial", 12);
	
	for (std::string name : cam_names)
		camera_list << QString::fromStdString(name);

	camera_select_combobox->addItems(camera_list);
	camera_select_combobox->setStyleSheet(white_color);
}
#include <thread>
void MakePhotoPage::CreateCameraArea()
{

	image_label_ = new QLabel(this);
	image_label_->setGeometry(190, 110, 440, 330);
	image_label_->show();
	//mdi_area = new QMdiArea(this);
	//x = 190;
	//y = 110;
	//width = 430;
	//height = 330;
	//mdi_area->setGeometry(QRect(x, y, width, height));

/*	for (int i = 0; i < 20; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		An<WebCamController>()->GetActiveCamera().GetFrame();
	}*/

	//image_scene = new QGraphicsScene(this);
	//image_scene->setSceneRect(100, 100, 430, 330);
	//image_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	//image = new QPixmap();
	//Frame f_img = An<WebCamController>()->GetActiveCamera().GetFrame();
	//QByteArray img_data(reinterpret_cast<const char*>(f_img.GetData()), 640 * 480 * 4);
	//image->loadFromData(img_data);
	//
	//image_scene->addPixmap(*image);
	//
	//image_view = new QGraphicsView(image_scene, this);
	////image_view->setSceneRect(190, 110, 430, 330);
	//image_view->setScene(image_scene);
	//image_view->show();
}

void MakePhotoPage::CreateButtons()
{
	button_font.setFamily(QStringLiteral("Arial"));
	button_font.setPointSize(10);
	gray_color = "background-color: rgb(225, 225, 225);";

	make_photo_button = new QPushButton(this);
	x = 210;
	y = 470;
	width = 90;
	height = 30;
	make_photo_button->setGeometry(QRect(x, y, width, height));
	make_photo_button->setFont(button_font);
	make_photo_button->setStyleSheet(gray_color);
	make_photo_button->setText("Make photo");

	x = 360;
	y = 470;
	width = 90;
	height = 30;
	accept_button = new QPushButton(this);
	accept_button->setGeometry(QRect(x, y, width, height));
	accept_button->setFont(button_font);
	accept_button->setStyleSheet(gray_color);
	accept_button->setText("Accept");
	accept_button->setDisabled(true);

	x = 500;
	y = 470;
	width = 90;
	height = 30;
	decline_button = new QPushButton(this);
	decline_button->setGeometry(QRect(x, y, width, height));
	decline_button->setFont(button_font);
	decline_button->setStyleSheet(gray_color);
	decline_button->setText("Decline");
	decline_button->setDisabled(true);
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
		An<WebCamController>()->ActivateCamera(An<WebCamController>()->GetCameras().at(1));
		is_enabled_ = true;
		worker_ = std::thread(&MakePhotoPage::CameraThread, this);
	}
}

void MakePhotoPage::MakePhoto()
{
	decline_button->setEnabled(true);
	accept_button->setEnabled(true);
	is_update_ = false;

	//for (int i = 0; i < 20; ++i)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//	An<WebCamController>()->GetActiveCamera().GetFrame();
	//}

	//Frame f_img = An<WebCamController>()->GetActiveCamera().GetFrame();

	//QImage img(640, 480, QImage::Format_RGBA8888);
	//for (int y = 0; y < 480; ++y)
	//{
	//	for (int x = 0; x < 640; ++x)
	//	{
	//		int index(y * 640 + x);
	//		img.setPixel(x, y, reinterpret_cast<int*>(f_img.GetData())[index]);
	//	}
	//}

	//QLabel image_label_;
	//image_label_.setPixmap(QPixmap::fromImage(img));
	//image_label_.setGeometry(100, 100, 640, 480);
	//image_label_.show();
}

