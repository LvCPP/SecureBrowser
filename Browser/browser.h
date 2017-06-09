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
	Browser(std::string link_to_quiz, std::string password_to_quiz, QWidget *parent = 0);
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
	QScopedPointer<Ui::Browser> ui_;
	std::string link_to_quiz_;
	std::string password_to_quiz_;
};

}