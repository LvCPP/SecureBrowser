#pragma once

#include "LoginApp2.h"

class WelcomePage : public QWizardPage
{
public:
	WelcomePage(QWidget *parent = 0);
	~WelcomePage();

	int nextId() const override;

private:
	void CreateWelcomePageBackground();
};