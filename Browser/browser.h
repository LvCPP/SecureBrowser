#pragma once

#include <QWidget>
#include <qwebenginehistory.h>
#include <qmessagebox.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtWebEngineCore/QWebEngineHttpRequest>
#include <QUrl>
#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkCookieJar>
#include <QList>

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
	QNetworkCookieJar* jar_;
	QNetworkAccessManager* manager_;
};

//class RemadedNetworkCookieJar : public QNetworkCookieJar
//{
//public:
//	RemadedNetworkCookieJar();
//	virtual ~RemadedNetworkCookieJar();
//	QList<QNetworkCookie> getAllCookies();
//	void setAllSitesCookies(const QList<QNetworkCookie>& cookieList);
//};

}