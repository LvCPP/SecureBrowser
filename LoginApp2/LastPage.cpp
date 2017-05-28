#include "LastPage.h"

using namespace Login;

LastPage::LastPage(QWidget *parent)
	: QWizardPage(parent)
{
	setFinalPage(true);
	CreateLastPageLabel();
}

LastPage::~LastPage()
{
}

void LastPage::CreateLastPageLabel()
{
	last_page_label = new QLabel(this);
	last_page_label->setText("You have finished the authentication process. Please get ready for the test");
	last_page_label->setAlignment(Qt::AlignHCenter);
	last_page_label->setGeometry(QRect(150, 160, 480, 300));
	QFont arial_22("Arial", 22);
	arial_22.setBold(true);
	last_page_label->setFont(arial_22);
	last_page_label->setWordWrap(true);
}