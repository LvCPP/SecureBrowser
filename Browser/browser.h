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
	Browser(std::string cookies, QWidget* parent = Q_NULLPTR);
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
	std::string cookies_;
	
};

}