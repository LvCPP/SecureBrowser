#include "LoginApp2.h"
#include "WelcomePage.h"

using namespace Login;

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
	backgr_name = "background-image: url(:/Resources/images/intro_background.jpg);";
	welcome_frame = new QFrame(this);
	frame_width = 800;
	frame_height = 520;
	welcome_frame->setGeometry(QRect(0, 0, frame_width, frame_height));
	welcome_frame->setStyleSheet(backgr_name);
}

int WelcomePage::nextId() const
{
	return LoginApp2::LOGIN_PAGE;
}
