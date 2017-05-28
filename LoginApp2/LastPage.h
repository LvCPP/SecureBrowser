#pragma once

#include "LoginApp2.h"

namespace Login
{

	class LastPage : public QWizardPage
	{
	public:
		LastPage(QWidget *parent = 0);
		~LastPage();

		void CreateLastPageLabel();

	private:
		QLabel* last_page_label;
	};

}