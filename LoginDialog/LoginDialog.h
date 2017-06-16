#pragma once
#include "ui_LoginDialog.h"
#include <LoginDialogUtils.h>
#include <Frame.h>

#include <QWidget>
#include <QCloseEvent>

#include <thread>

using namespace CameraInspector;

namespace Login
{

class LoginDialog : public QWizard
{
	Q_OBJECT

public:
	explicit LOGIN_DIALOG_API LoginDialog(std::string login, std::string password, std::string path, QWidget* parent = Q_NULLPTR);
	explicit LOGIN_DIALOG_API LoginDialog(QWidget* parent = Q_NULLPTR);
	LOGIN_DIALOG_API ~LoginDialog() = default;

	LOGIN_DIALOG_API void GetMoodleSession(std::string& session) const;

private:
	void initializePage(int id) override;	
	int nextId() const override;
	void closeEvent(QCloseEvent* close_button) override;

	void CameraThread();
	void RefreshComboBox();
	void InitCamera();

	enum
	{
		WELCOME_PAGE
		, LOGIN_PAGE
		, MAKE_PHOTO_PAGE
		, LAST_PAGE
	};

	QScopedPointer<Ui::Wizard> ui_;
	
	std::string moodle_session_;
	bool is_login_checked_;
	Frame id_frame_;
	mutable std::thread worker_;
	mutable bool is_frame_enabled_;
	bool is_frame_updated_;
	bool is_photo_made_;
	QStringList camera_list_;
	std::string login_;
	std::string password_;
	std::string path_;
	
signals:
	void UpdateImage(QPixmap image);
	void LoginAccepted();

private slots:
	void ChooseCamera(int id);
	void TakePhoto();
	void AcceptPhotoButtonClicked();
	void DeclinePhotoButtonClicked();
	
public slots:
	void CheckLogin();
};

} // namespace Login
