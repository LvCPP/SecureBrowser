#include "ui_LoginDialog.h"
#include "LoginDialog.h"
#include <Logger.h>
#include <WebCamController.h>
#include <FileSystemFrameSaver.h>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <QString>
#include <QMessageBox>
#include <QImage>
#include <QSettings>

#include <string>
#include <functional>
#include <map>

//for testing 
#include <QtDebug>

// for disabling redirect
#pragma comment(lib, "winhttp.lib")
#include <windows.h>
#include <winhttp.h>

using namespace utility::conversions;
using namespace web;
using namespace web::http;
using namespace web::http::client;

using namespace Login;
using namespace Utils;
using namespace CameraInspector;

using utf8string = std::string;  // alias for working with http_client

// for working with registry
static const QString reg_path = "HKEY_CURRENT_USER\\Software\\SoftServe\\SecureBrowser";
static const QString reg_group_name = "Run";
static const QString reg_value_name = "FirstRun";

LoginDialog::LoginDialog(std::string login, std::string password, std::string path, QWidget* parent)
	: QWizard(parent)
	, is_frame_enabled_(true)
	, is_login_checked_(false)
	, is_frame_updated_(true)
	, is_photo_made_(false)
	, login_(login)
	, password_(password)
	, path_(path)
{
	ui_ = new Ui::Wizard;
	ui_->setupUi(this);

	this->setWindowFlags(Qt::Window
		| Qt::WindowTitleHint
		| Qt::CustomizeWindowHint
		| Qt::MSWindowsFixedSizeDialogHint
		| Qt::WindowCloseButtonHint);

	QList<QWizard::WizardButton> layout;
	layout << QWizard::Stretch << QWizard::NextButton << QWizard::FinishButton;
	this->setButtonLayout(layout);

	connect(ui_->take_photo_button, SIGNAL(clicked()), this, SLOT(TakePhoto()));
	connect(this, SIGNAL(UpdateImage(QPixmap)), ui_->image_label, SLOT(setPixmap(QPixmap)));
	connect(ui_->camera_select_combobox, SIGNAL(activated(int)), this, SLOT(ChooseCamera(int)));
	connect(ui_->decline_photo_button, SIGNAL(clicked()), this, SLOT(DeclinePhotoButtonClicked()));
	connect(ui_->accept_photo_button, SIGNAL(clicked()), this, SLOT(AcceptPhotoButtonClicked()));
}

LoginDialog::~LoginDialog()
{
	delete ui_;
}

int LoginDialog::nextId() const
{
	switch (currentId())
	{
	case WELCOME_PAGE:
		return LOGIN_PAGE;
	case LOGIN_PAGE:
		if (is_login_checked_)
			return MAKE_PHOTO_PAGE;
		else
			return LOGIN_PAGE;
	case MAKE_PHOTO_PAGE:
		if (is_photo_made_)
		{
			is_frame_enabled_ = false;
			if (worker_.joinable())
				worker_.join();
			return LAST_PAGE;
		}
		else
		{
			return MAKE_PHOTO_PAGE;
		}
	case LAST_PAGE:
	default:
		return -1;
	}
}

void LoginDialog::CheckLogin()
{
	std::string username = ui_->username_lineedit->text().toStdString();
	std::string password = ui_->password_lineedit->text().toStdString();
	std::string body_text = "username=" + username + "&password=" + password + "&anchor=";
	utf8string request_body = body_text;
	utf8string content_type = "application/x-www-form-urlencoded";

	// disabling redirect
	http_client_config config;
	config.set_nativehandle_options([](native_handle handle)
	{
		DWORD data = WINHTTP_DISABLE_REDIRECTS;
		BOOL res = WinHttpSetOption(handle, WINHTTP_OPTION_DISABLE_FEATURE, &data, sizeof(data));
		if (!res)
		{
			DWORD error = GetLastError();
		}
		else
		{
			qDebug() << "Redirect disabled\n";
		}
	});

	utility::string_t base_url = U("https://softserve.academy");
	http_client client(base_url, config);
		
	http_request req(methods::POST);
	req.set_request_uri(U("/login/index.php"));

	req.set_body(body_text, content_type);
	http_response response = client.request(req).get();
	
	http_headers& resp_headers = response.headers();
	for (std::map<utility::string_t
		, utility::string_t>::iterator it
		= resp_headers.begin()
		; it != resp_headers.end()
		; ++it)
	{
		if (to_utf8string(it->first) == "Set-Cookie")
		{
			std::size_t found = to_utf8string(it->second).find("MOODLEID1_=deleted");
			if (found != std::string::npos)
			{
				if (QMessageBox::information(this, tr("Login"),
					tr("<p align='center'>User found. You are logged in!</p>"), QMessageBox::Ok) == QMessageBox::Ok)
				{
					is_login_checked_ = true;
					ui_->username_lineedit->setEnabled(false);
					ui_->password_lineedit->setEnabled(false);
					ui_->agree_checkbox->setEnabled(false);
					ui_->login_button->setEnabled(false);
				}
			}
			else
			{
				if (QMessageBox::warning(this, tr("Login"),
					tr("<p align='center'>User not found.<br>"
						"Please provide correct username and password!</p>"),
					QMessageBox::Ok) == QMessageBox::Ok)
				{
					ui_->username_lineedit->setText(QString::fromStdString(login_));
					ui_->password_lineedit->setText(QString::fromStdString(password_));
					ui_->agree_checkbox->setCheckState(Qt::Unchecked);
				}
			}
		}
		else
		{
			continue;
		}
	}
}

void LoginDialog::CameraThread()
{
	while (is_frame_enabled_)
	{
		if (is_frame_updated_)
		{
			id_frame_ = An<WebCamController>()->GetActiveCamera().GetFrame();

			QImage img(640, 480, QImage::Format_RGB32);
			int index = 0;
			for (int y = 0; y < 480; ++y)
			{
				for (int x = 0; x < 640; ++x)
				{
					index = y * 640 + x;
					img.setPixel(x, y, reinterpret_cast<int*>(id_frame_.GetData())[index]);
				}
			}
			img = img.scaled(400, 300, Qt::KeepAspectRatio);
			QPixmap pixmap = QPixmap::fromImage(img);
			emit UpdateImage(pixmap.copy());
		}
	}
}

void LoginDialog::RefreshComboBox()
{
	An<WebCamController> wcc;
	std::vector<std::string> cam_names = wcc->ListNamesOfCameras();
	camera_list_.clear();
	ui_->camera_select_combobox->clear();
	for (std::string name : cam_names)
		camera_list_ << QString::fromStdString(name);
	ui_->camera_select_combobox->addItems(camera_list_);
}

void LoginDialog::InitCamera()
{
	An<WebCamController> wcc;
	wcc->ActivateCamera(wcc->GetCameras().at(0));
	
	wcc->SetRefreshCallback(std::bind(&LoginDialog::RefreshComboBox, this));
		
	is_frame_enabled_ = true;
			
	worker_ = std::thread(&LoginDialog::CameraThread, this);
}

void LoginDialog::initializePage(int id)
{
	switch (id)
	{
	case WELCOME_PAGE:
		return;
	case LOGIN_PAGE:
		ui_->login_button->setEnabled(false);
		ui_->username_lineedit->setText(QString::fromStdString(login_));
		ui_->password_lineedit->setText(QString::fromStdString(password_));
		ui_->agree_checkbox->setCheckState(Qt::Unchecked);
		connect(ui_->login_button, SIGNAL(clicked()), this, SLOT(CheckLogin()));
		connect(ui_->agree_checkbox, SIGNAL(toggled(bool)), ui_->login_button, SLOT(setEnabled(bool)));
		return;
	case MAKE_PHOTO_PAGE:
		RefreshComboBox();
		InitCamera();
		return;
	case LAST_PAGE:
	default: return;
	}
}

void LoginDialog::TakePhoto()
{
	is_frame_updated_ = false;
	ui_->decline_photo_button->setEnabled(true);
	ui_->accept_photo_button->setEnabled(true);
	ui_->take_photo_button->setDisabled(true);
	QMessageBox::warning(this, tr("Photo has been taken"),
		tr("<p align='center'>You have to accept the photo<br>"
			"or make another one using Decline photo button</p>"),
		QMessageBox::Ok);
}

void LoginDialog::ChooseCamera(int id)
{
	An<WebCamController>()->ActivateCamera(An<WebCamController>()->GetCameras().at(id));
}

void LoginDialog::DeclinePhotoButtonClicked()
{
	ui_->take_photo_button->setEnabled(true);
	ui_->accept_photo_button->setDisabled(true);
	ui_->decline_photo_button->setDisabled(true);
	is_frame_updated_ = true;
	QMessageBox::warning(this, tr("Decline photo"),
		tr("<p align='center'>You can take another photo using Take photo button<br>"
			"or proceed if your photo has already been accepted</p>"),
		QMessageBox::Ok);
}

void LoginDialog::AcceptPhotoButtonClicked()
{
	ui_->accept_photo_button->setEnabled(false);
	FileSystemFrameSaver saver;
	saver.SetNameToSave("ID_photo");
	saver.SetPathToSave(path_ + "Photos\\");
	saver.Save(id_frame_);
	is_photo_made_ = true;
	QMessageBox::warning(this, tr("Photo has been accepted "),
		tr("<p align='center'>You can proceed now clicking on Next button<br>"
			"or make another photo using Decline photo button</p>"),
		QMessageBox::Ok);
}

void LoginDialog::closeEvent(QCloseEvent* close_button)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this
		, tr("Quit application")
		, tr("<p align='center'>Do you really want to quit the authentication process?</p>")
		, QMessageBox::Yes | QMessageBox::No
		, QMessageBox::No);
	if (resBtn != QMessageBox::Yes)
		close_button->ignore();
	else
	{
		close_button->accept();
		is_frame_enabled_ = false;
		if (worker_.joinable())
			worker_.join();
	}
}

/* Use this function if you want to write to the registry 
 the keys defining the first run of the application on PC. */
void LoginDialog::SetFirstRunSetting()
{
	QSettings setting(reg_path);
	setting.setDefaultFormat(QSettings::Registry64Format);
	// Windows only:
	// Explicitly access the 64-bit system registry from a 32-bit application running on 64-bit Windows.
	// On 32-bit Windows or from a 64-bit application on 64-bit Windows, this works the same as
	// specifying NativeFormat. Was added in Qt 5.7.

	setting.beginGroup(reg_group_name);
	bool first_run = false;
	setting.setValue(reg_value_name, first_run);
	setting.endGroup();
}

/* Use this function if you want to know whether the application 
is run on PC for the first time or not. */
bool LoginDialog::IsFirstRun()
{
	QSettings setting(reg_path);
	setting.setDefaultFormat(QSettings::Registry64Format);
	setting.beginGroup(reg_group_name);
	QStringList keys = setting.childKeys();
	if (!keys.contains(reg_value_name, Qt::CaseInsensitive))
		return true;
	else
		return false;
	setting.endGroup();
}

/* Use thus function if you want to remove first run settings
from the registry. */
void LoginDialog::RemoveFirstRunSetting()
{
	QSettings setting(reg_path);
	setting.setDefaultFormat(QSettings::Registry64Format);
	setting.beginGroup(reg_group_name);
	setting.remove(reg_value_name);
	setting.endGroup();
}