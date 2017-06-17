#pragma once

#include <qwebenginehistory.h>
#include <qmessagebox.h>

#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtWebEngineCore/QWebEngineCookieStore>
#include <QUrl>

namespace Ui 
{ 
class Browser;
class QWebEngineHistory;
class QMessageBox;
} // namespace Ui

namespace SecureBrowser
{

class Browser : public QWidget
{
	Q_OBJECT

public:
	explicit Browser(std::string link_to_quiz, std::string password_to_quiz, std::string cookies, QWidget* parent = Q_NULLPTR);
	~Browser();

private slots:
	void SlotEnter() const;
	void SetUrl(const QUrl &url) const;
	void SetNewTitle() const;
	void ShowProgressBar() const;
	void HideProgressBar() const;
	void ButtonBackHistory() const;
	void ButtonForwardHistory() const;
	void CloseButton();
	
private:
	QScopedPointer<Ui::Browser> ui_;
	std::string link_to_quiz_;
	std::string password_to_quiz_;
	std::string cookies_;
	QWebEngineProfile* profile_;
	QWebEngineCookieStore* store_;
};

} // namespace SecureBrowser