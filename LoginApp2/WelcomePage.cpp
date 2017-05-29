#include "WelcomePage.h"

#include <QString>
#include <QFrame>

using namespace Login;

static QString backgr_name = "background-image: url(:/Resources/images/intro_background.jpg);";

WelcomePage::WelcomePage(QWidget *parent)
	: QWizardPage(parent)

{
	CreateWelcomePageBackground();
}

WelcomePage::~WelcomePage()
{
}

void WelcomePage::CreateWelcomePageBackground()
{
	QFrame* welcome_frame = new QFrame(this);
	welcome_frame->setGeometry(QRect(0, 0, 800, 520));
	welcome_frame->setStyleSheet(backgr_name);
}

int WelcomePage::nextId() const
{
	return LoginApp2::LOGIN_PAGE;
}
