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
	explicit Browser(std::string quiz_id, std::string password_to_quiz, std::string cookies, QWidget* parent = Q_NULLPTR);
	~Browser();

private slots:
	void ShowProgressBar() const;
	void HideProgressBar() const;
	void SetNewTitle() const;
	void ButtonBackHistory() const;
	void ButtonForwardHistory() const;
	void CloseButton();
	void SetQuizPassword();
	
private:
	QScopedPointer<Ui::Browser> ui_;
	std::string quiz_id_;
	std::string password_to_quiz_;
	std::string cookies_;
	QWebEngineProfile* profile_;
	QWebEngineCookieStore* store_;
};

} // namespace SecureBrowser