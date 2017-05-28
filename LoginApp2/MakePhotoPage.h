#pragma once

#include "LoginApp2.h"

#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qimage.h>
#include <thread>

namespace Login
{

class MakePhotoPage : public QWizardPage
{
	Q_OBJECT
public:
	MakePhotoPage(QWidget *parent = 0);
	~MakePhotoPage();

	int nextId() const override;

	void CreateCameraSelectLabel();
	void CreateCameraSelectComboBox();
	void CreateCameraArea();
	void CreateButtons();

public slots:
	void InitCamera();

private slots:
	void MakePhoto();
	void OnCameraChoose(int id);

private:
	void CameraThread();

	QLabel* camera_select_label;
	QLabel* image_label_;
	QComboBox* camera_select_combobox;
	QString white_color;
	QStringList camera_list;
	//QMdiArea* mdi_area;

	QGraphicsView* image_view;
	QGraphicsScene* image_scene;
	QPixmap* image;

	QString gray_color;
	QFont button_font;
	QPushButton* make_photo_button;
	QPushButton* accept_button;
	QPushButton* decline_button;
	int x;
	int y;
	int width;
	int height;

	std::thread worker_;
	mutable bool is_enabled_;
	bool is_update_;
};

}