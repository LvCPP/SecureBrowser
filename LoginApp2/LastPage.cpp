#include "LastPage.h"

#include <QLabel>
#include <QFont>

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
	QLabel* last_page_label = new QLabel(this);
	last_page_label->setText("You have finished the authentication process. Please get ready for the test!");
	last_page_label->setAlignment(Qt::AlignHCenter);
	last_page_label->setGeometry(QRect(150, 160, 300, 300));
	QFont arial_12("Arial", 12);
	arial_12.setBold(true);
	last_page_label->setFont(arial_12);
	last_page_label->setWordWrap(true);
}