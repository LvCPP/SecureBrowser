#pragma once

#include "LoginApp2.h"

class WelcomePage : public QWizardPage
{
public:
	WelcomePage(QWidget *parent = 0);
	~WelcomePage();
	void CreateWelcomePageBackground();

	int nextId() const override;

private:
	QString backgr_name;
	QFrame* welcome_frame;
	int frame_width;
	int frame_height;
};