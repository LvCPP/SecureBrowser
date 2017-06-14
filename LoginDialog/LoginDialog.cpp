#include "LoginDialog.h"
#include <An.hpp>
#include <Logger.h>
#include <WebCamController.h>
#include <FileSystemFrameSaver.h>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <QString>
#include <QMessageBox>
#include <QImage>

#include <functional>
#include <map>

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
using namespace BrowserLogger;

// alias for working with http_client
using utf8string = std::string;

// constructor for the test project
LoginDialog::LoginDialog(QWidget* parent)
	: QWizard(parent)
	, ui_(new Ui::Wizard)
	, is_login_checked_(false)
	, is_frame_enabled_(true)
	, is_frame_updated_(true)
	, is_photo_made_(false)
{
	ui_->setupUi(this);

	this->setWindowFlags(Qt::Window
		| Qt::WindowTitleHint
		| Qt::CustomizeWindowHint
		| Qt::MSWindowsFixedSizeDialogHint
		| Qt::WindowCloseButtonHint);

	QList<WizardButton> layout;
	layout << Stretch << NextButton << FinishButton;
	this->setButtonLayout(layout);

}

LoginDialog::LoginDialog(std::string login, std::string password, std::string path, QWidget* parent)
	: QWizard(parent)
	, ui_(new Ui::Wizard)
	, is_login_checked_(false)
	, is_frame_enabled_(true)
	, is_frame_updated_(true)
	, is_photo_made_(false)
	, login_(login)
	, password_(password)
	, path_(path)
{
	ui_->setupUi(this);

	this->setWindowFlags(Qt::Window
		| Qt::WindowTitleHint
		| Qt::CustomizeWindowHint
		| Qt::MSWindowsFixedSizeDialogHint
		| Qt::WindowCloseButtonHint);

	QList<WizardButton> layout;
	layout << Stretch << NextButton << FinishButton;
	this->setButtonLayout(layout);
}

void LoginDialog::initializePage(int id)
{
	switch (id)
	{
	case LOGIN_PAGE:
		ui_->login_button->setEnabled(false);
		ui_->username_lineedit->setText(QString::fromStdString(login_));
		ui_->password_lineedit->setText(QString::fromStdString(password_));
		ui_->agree_checkbox->setCheckState(Qt::Unchecked);
		connect(ui_->login_button, SIGNAL(clicked()), this, SLOT(CheckLogin()));
		connect(ui_->agree_checkbox, SIGNAL(toggled(bool)), ui_->login_button, SLOT(setEnabled(bool)));
		break;
	case MAKE_PHOTO_PAGE:
		RefreshComboBox();
		InitCamera();
		connect(ui_->take_photo_button, SIGNAL(clicked()), this, SLOT(TakePhoto()));
		connect(this, SIGNAL(UpdateImage(QPixmap)), ui_->image_label, SLOT(setPixmap(QPixmap)));
		connect(ui_->camera_select_combobox, SIGNAL(activated(int)), this, SLOT(ChooseCamera(int)));
		connect(ui_->decline_photo_button, SIGNAL(clicked()), this, SLOT(DeclinePhotoButtonClicked()));
		connect(ui_->accept_photo_button, SIGNAL(clicked()), this, SLOT(AcceptPhotoButtonClicked()));
		break;
	case WELCOME_PAGE:
	case LAST_PAGE:
	default:
		break;
	}
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

// for sending cookies to the browser
void LoginDialog::GetMoodleSession(std::string& session) const
{
	session = moodle_session_;
}

void LoginDialog::CheckLogin()
{
	std::string username = ui_->username_lineedit->text().toStdString();
	std::string password = ui_->password_lineedit->text().toStdString();
	std::string body_text = "username=" + username + "&password=" + password + "&anchor=";
	utf8string request_body = body_text;
	utf8string content_type = "application/x-www-form-urlencoded";

	 //for disabling redirect
	http_client_config config;
	config.set_nativehandle_options([](native_handle handle)
	{
		DWORD data = WINHTTP_DISABLE_REDIRECTS;
		BOOL res = WinHttpSetOption(handle, WINHTTP_OPTION_DISABLE_FEATURE, &data, sizeof(data));
		if (!res)
		{
			DWORD error = GetLastError();
			logwarning(*An<Logger>()) << "Could not disable redirect with error " << error;
		}
		else
		{
			logdebug(*An<Logger>()) << "Redirect disabled.";
		}
	});

	utility::string_t base_url = U("https://softserve.academy/");
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
			size_t found = to_utf8string(it->second).find("MOODLEID");
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
					loginfo(*An<Logger>()) << "User was logged in.";
				}
				size_t moodle_session_pos = to_utf8string(it->second).find("MoodleSession");
				size_t semicolon_pos = to_utf8string(it->second).find(";", moodle_session_pos);
				this->moodle_session_ = to_utf8string(it->second).substr(moodle_session_pos, semicolon_pos - moodle_session_pos);
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
					this->moodle_session_ = "";
					loginfo(*An<Logger>()) << "User was not logged in.";
				}
			}
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

void LoginDialog::ChooseCamera(int id)
{
	An<WebCamController>()->ActivateCamera(An<WebCamController>()->GetCameras().at(id));
}

void LoginDialog::InitCamera()
{
	An<WebCamController> wcc;
	wcc->ActivateCamera(wcc->GetCameras().at(0));

	wcc->SetRefreshCallback(std::bind(&LoginDialog::RefreshComboBox, this));

	is_frame_enabled_ = true;

	worker_ = std::thread(&LoginDialog::CameraThread, this);
}

void LoginDialog::CameraThread()
{
	while (is_frame_enabled_)
	{
		if (is_frame_updated_)
		{
			id_frame_ = An<WebCamController>()->GetActiveCamera().GetFrame();

			QImage img(640, 480, QImage::Format_RGB32);
			for (int y = 0; y < 480; ++y)
			{
				for (int x = 0; x < 640; ++x)
				{
					int index = y * 640 + x;
					img.setPixel(x, y, reinterpret_cast<int*>(id_frame_.GetData())[index]);
				}
			}
			img = img.scaled(400, 300, Qt::KeepAspectRatio);
			QPixmap pixmap = QPixmap::fromImage(img);
			emit UpdateImage(pixmap.copy());
		}
	}
}

void LoginDialog::TakePhoto()
{
	is_frame_updated_ = false;
	ui_->decline_photo_button->setEnabled(true);
	ui_->accept_photo_button->setEnabled(true);
	ui_->take_photo_button->setDisabled(true);
	QMessageBox::warning(this, tr("Photo has been taken"),
		tr("<p align='center'>You may save the photo or take another one<br>"
			"on pushing the decline photo button</p>"),
		QMessageBox::Ok);
}

void LoginDialog::DeclinePhotoButtonClicked()
{
	ui_->take_photo_button->setEnabled(true);
	ui_->accept_photo_button->setDisabled(true);
	ui_->decline_photo_button->setDisabled(true);
	is_frame_updated_ = true;
	loginfo(*An<Logger>()) << "User's ID photo declined.";
}

void LoginDialog::AcceptPhotoButtonClicked()
{
	ui_->accept_photo_button->setEnabled(false);
	ui_->decline_photo_button->setEnabled(false);

	FileSystemFrameSaver saver;
	saver.SetNameToSave("ID_photo");
	saver.SetPathToSave(path_ + "Photos\\");
	saver.Save(id_frame_);
	is_photo_made_ = true;
	loginfo(*An<Logger>()) << "User's ID photo saved to disk.";
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
