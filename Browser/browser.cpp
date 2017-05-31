#include "browser.h"
#include "ui_browser.h"

using namespace SecureBrowser;

Browser::Browser(QWidget *parent)
	: QWidget(parent)
	, ui_(new Ui::Browser())
{
	ui_->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setWindowState(Qt::WindowFullScreen);
	connect(ui_->line_edit, &QLineEdit::returnPressed, this, &Browser::SlotEnter);
	connect(ui_->push_btn_back, &QPushButton::clicked, ui_->web_view, &QWebEngineView::back);
	connect(ui_->push_btn_forward, &QPushButton::clicked, ui_->web_view, &QWebEngineView::forward);
	connect(ui_->push_btn_reload, &QPushButton::clicked, ui_->web_view, &QWebEngineView::reload);
	connect(ui_->push_btn_stop, &QPushButton::clicked, ui_->web_view, &QWebEngineView::stop);
	connect(ui_->push_btn_close, &QPushButton::clicked, this, &Browser::CloseButton);
	connect(ui_->web_view, &QWebEngineView::loadProgress, ui_->load_progress_page, &QProgressBar::setValue);
	connect(ui_->web_view, &QWebEngineView::loadStarted, this, &Browser::ShowProgressBar);
	connect(ui_->web_view, &QWebEngineView::loadFinished, this, &Browser::HideProgressBar);
	connect(ui_->web_view, &QWebEngineView::urlChanged, this, &Browser::SetUrl);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::SetMyTitle);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::ButtonBackHistory);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::ButtonForwardHistory);
	ui_->push_btn_back->setEnabled(false);
	ui_->push_btn_forward->setEnabled(false);
	ui_->push_btn_reload->setEnabled(false);
	ui_->web_view->setContextMenuPolicy(Qt::NoContextMenu);
	ui_->web_view->load(QUrl("https://softserve.academy"));
}

Browser::~Browser()
{
}

void Browser::SlotEnter()
{
	QUrl url = QUrl::fromUserInput(ui_->line_edit->text());
	ui_->web_view->load(url);
}

void Browser::SetUrl(const QUrl &url)
{
	ui_->line_edit->setText(url.toString());
}

void Browser::SetMyTitle()
{
	ui_->label->setText(ui_->web_view->title());
}

void Browser::ShowProgressBar()
{
	ui_->load_progress_page->show();
	ui_->push_btn_reload->setEnabled(false);
	ui_->push_btn_stop->setEnabled(true);
}

void Browser::HideProgressBar()
{
	ui_->load_progress_page->hide();
	ui_->push_btn_reload->setEnabled(true);
	ui_->push_btn_stop->setEnabled(false);
}

void Browser::ButtonBackHistory()
{
	if (ui_->web_view->history()->canGoBack())
		ui_->push_btn_back->setEnabled(true);
	else
		ui_->push_btn_back->setEnabled(false);
}

void Browser::ButtonForwardHistory()
{
	if (ui_->web_view->history()->canGoForward())
		ui_->push_btn_forward->setEnabled(true);
	else
		ui_->push_btn_forward->setEnabled(false);
}

void Browser::CloseButton()
{
	QMessageBox::StandardButtons reply;
	reply = QMessageBox::question(this, "Warning", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
		Browser::close();
}
