#pragma once
#include<QtWidgets/QWidget>
#include<QObject>
#include<memory>
#include<qstackedwidget.h>

namespace BrowserLogin
{

class LoginAppPrivate;
class LoginApp: public QStackedWidget
{
	Q_OBJECT
public:
	explicit LoginApp(QWidget* parent = Q_NULLPTR);
	~LoginApp();
signals:
	void AcceptPhotoClicked();
	void RejectClicked();
protected:
	LoginAppPrivate* const d_ptr;
private:
	Q_PRIVATE_SLOT(d_func(), void _q_OnPushButtonLoginClick())
	Q_PRIVATE_SLOT(d_func(), void _q_PhotoAccepted())
	Q_DECLARE_PRIVATE(LoginApp)
};

}


