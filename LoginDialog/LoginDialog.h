#pragma once
#include "ui_LoginDialog.h"
#include <LoginDialogUtils.h>
#include <StableFrame.h>
#include <Frame.h>
#include <CameraInspectorUtils.h>

#include <QWidget>
#include <QtWidgets/QDialog>
#include <QStringList>
#include <QCloseEvent>

#include <thread>

using namespace CameraInspector;

namespace Login
{

class LoginDialog : public QWizard
{
	Q_OBJECT

public:
	LOGIN_DIALOG_API LoginDialog(std::string login, std::string password, QWidget* parent = Q_NULLPTR);
	LOGIN_DIALOG_API ~LoginDialog();

private:
	void CameraThread();
	void RefreshComboBox();
	void InitCamera();

	int nextId() const override;
	void initializePage(int id) override;
	void closeEvent(QCloseEvent* close_button) override;

	void SetFirstRunSetting();
	bool IsFirstRun();
	void RemoveFirstRunSetting();

	enum
	{
		WELCOME_PAGE
		, LOGIN_PAGE
		, MAKE_PHOTO_PAGE
		, LAST_PAGE
	};

	Ui::Wizard* ui_;

	bool is_login_checked_;
	Frame id_frame_;
	mutable std::thread worker_;
	mutable bool is_frame_enabled_;
	bool is_frame_updated_;
	bool is_photo_made_;
	QStringList camera_list_;
	std::string login_;
	std::string password_;
	
signals:
	void UpdateImage(QPixmap image);
	
private slots:
	void TakePhoto();
	void ChooseCamera(int id);
	void DeclinePhotoButtonClicked();
	void AcceptPhotoButtonClicked();
	void CheckLogin();
	
};

}
