#pragma once

#include <QWidget>
#include <qwebenginehistory.h>

namespace Ui 
{ 
class Browser;
class QWebEngineHistory;
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

private:
	QScopedPointer<Ui::Browser> ui_;
};

}