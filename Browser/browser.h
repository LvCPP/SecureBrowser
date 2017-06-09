#pragma once

#include <QWidget>
#include <qwebenginehistory.h>
#include <qmessagebox.h>

#include <string>

namespace Ui 
{ 
class Browser;
class QWebEngineHistory;
class QMessageBox;
}

namespace SecureBrowser
{

class Browser : public QWidget
{
	Q_OBJECT

public:
	Browser(QWidget *parent = 0);
	~Browser();

private slots:
	void SlotEnter();
	void SetUrl(const QUrl &url);
	void SetMyTitle();
	void ShowProgressBar();
	void HideProgressBar();
	void ButtonBackHistory();
	void ButtonForwardHistory();
	void CloseButton();
	
private:
	/*std::string GetMoodleSession();
	void SetMoodleSession();*/
	QScopedPointer<Ui::Browser> ui_;
	/*std::string moodle_session_;*/
	
};

}