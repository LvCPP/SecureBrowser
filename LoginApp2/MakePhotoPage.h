#pragma once

#include "LoginApp2.h"
#include "../CameraInspector/StableFrame.h"

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QComboBox>

#include <thread>

using namespace CameraInspector;

namespace Login
{

class MakePhotoPage : public QWizardPage
{
	Q_OBJECT
public:
	MakePhotoPage(QWidget *parent = 0);
	~MakePhotoPage();

	int nextId() const override;
	void initializePage() override;

	void CreateCameraSelectLabel();
	void CreateCameraSelectComboBox();
	void CreateCameraArea();
	void CreateButtons();

private slots:
	void MakePhoto();
	void OnCameraChoose(int id);
	void DeclineButtonClicked();
	void AcceptButtonClicked();

private:
	void CameraThread();
	void RefreshComboBox();
	void InitCamera();

	Frame id_frame_;

	QComboBox* camera_select_combobox_;
	QStringList camera_list_;
	QLabel* image_label_;

	QPushButton* make_photo_button_;
	QPushButton* accept_button_;
	QPushButton* decline_button_;
		
	std::thread worker_;
	mutable bool is_enabled_;
	bool is_update_;
	bool photo_made_;
};

}