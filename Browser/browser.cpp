#include "browser.h"
#include "ui_browser.h"
#include <Logger.h>

#include <QtNetwork/QNetworkCookie>
#include <QtWebEngineCore/QWebEngineHttpRequest>

using namespace SecureBrowser;
using namespace Utils;
using namespace BrowserLogger;

Browser::Browser(std::string quiz_id, std::string password_to_quiz, std::string cookies, QWidget *parent)
	: QWidget(parent)
	, ui_(new Ui::Browser())
	, quiz_id_(quiz_id)
	, password_to_quiz_(password_to_quiz)
	, cookies_(cookies)
{
	ui_->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::CustomizeWindowHint);
	
	connect(ui_->push_btn_back, &QPushButton::clicked, ui_->web_view, &QWebEngineView::back);
	connect(ui_->push_btn_forward, &QPushButton::clicked, ui_->web_view, &QWebEngineView::forward);
	connect(ui_->push_btn_reload, &QPushButton::clicked, ui_->web_view, &QWebEngineView::reload);
	connect(ui_->push_btn_stop, &QPushButton::clicked, ui_->web_view, &QWebEngineView::stop);
	connect(ui_->push_btn_close, &QPushButton::clicked, this, &Browser::CloseButton);
	connect(ui_->web_view, &QWebEngineView::loadProgress, ui_->load_progress_page, &QProgressBar::setValue);
	connect(ui_->web_view, &QWebEngineView::loadStarted, this, &Browser::ShowProgressBar);
	connect(ui_->web_view, &QWebEngineView::loadFinished, this, &Browser::HideProgressBar);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::SetNewTitle);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::ButtonBackHistory);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::ButtonForwardHistory);
	connect(ui_->web_view, &QWebEngineView::loadFinished, this, &Browser::SetQuizPassword);

	ui_->push_btn_back->setEnabled(false);
	ui_->push_btn_forward->setEnabled(false);
	ui_->push_btn_reload->setEnabled(false);
	ui_->web_view->setContextMenuPolicy(Qt::NoContextMenu);

	// for connecting with the Moodle server
	profile_ = new QWebEngineProfile(this);
	QUrl base_url = QUrl(QString::fromStdString("https://softserve.academy"));

	store_ = ui_->web_view->page()->profile()->cookieStore();
	std::string cookie_number = cookies_.substr(14, cookies_.length() - 14);
	QNetworkCookie moodle_cookie("MoodleSession", cookie_number.c_str());
	store_->setCookie(moodle_cookie, base_url);
	store_->loadAllCookies();
	
	ui_->web_view->load(QUrl(QString::fromStdString("https://softserve.academy/mod/quiz/view.php?id=" + quiz_id_)));
}

Browser::~Browser()
{
}

void Browser::ShowProgressBar() const
{
	ui_->load_progress_page->show();
	ui_->push_btn_reload->setEnabled(false);
	ui_->push_btn_stop->setEnabled(true);
}

void Browser::HideProgressBar() const
{
	ui_->load_progress_page->hide();
	ui_->push_btn_reload->setEnabled(true);
	ui_->push_btn_stop->setEnabled(false);
}

void Browser::SetNewTitle() const
{
	ui_->label->setText(ui_->web_view->title());
}


void Browser::ButtonBackHistory() const
{
	if (ui_->web_view->history()->canGoBack())
		ui_->push_btn_back->setEnabled(true);
	else
		ui_->push_btn_back->setEnabled(false);
}

void Browser::ButtonForwardHistory() const
{
	if (ui_->web_view->history()->canGoForward())
		ui_->push_btn_forward->setEnabled(true);
	else
		ui_->push_btn_forward->setEnabled(false);
}

void Browser::CloseButton()
{
	QMessageBox::StandardButtons reply = QMessageBox::question(this
		, "Warning"
		, "<p align = 'center'>Do you really want to quit SecureBrowser and finish the test? </p>"
		, QMessageBox::Yes | QMessageBox::No
		, QMessageBox::No);

	if (reply == QMessageBox::Yes)
		close();
}

void Browser::SetQuizPassword()
{
	ui_->web_view->page()->toHtml([&](QString html)
	{
		if (html.indexOf("id=\"id_quizpassword\" value=\"\"") != -1)
		{
			QString test = html.replace("id=\"id_quizpassword\" value=\"\"", QString::fromStdString("id=\"id_quizpassword\" value=\"" + password_to_quiz_ + "\" readonly"));

			ui_->web_view->setHtml(html);
		}
	});
}