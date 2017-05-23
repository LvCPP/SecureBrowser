#include "browser.h"
#include "ui_browser.h"

using namespace SecureBrowser;

Browser::Browser(QWidget *parent)
	: QWidget(parent)
	, ui_(new Ui::Browser())
{
	ui_->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	//setWindowState(Qt::WindowMaximized);
	setWindowState(Qt::WindowFullScreen);
	connect(ui_->line_edit, &QLineEdit::returnPressed, this, &Browser::SlotEnter);
	connect(ui_->push_btn_back, &QPushButton::clicked, ui_->web_view, &QWebEngineView::back);
	connect(ui_->push_btn_forward, &QPushButton::clicked, ui_->web_view, &QWebEngineView::forward);
	connect(ui_->push_btn_reload, &QPushButton::clicked, ui_->web_view, &QWebEngineView::reload);
	connect(ui_->push_btn_stop, &QPushButton::clicked, ui_->web_view, &QWebEngineView::stop);
	connect(ui_->web_view, &QWebEngineView::loadProgress, ui_->load_progress_page, &QProgressBar::setValue);
	connect(ui_->web_view, &QWebEngineView::loadStarted, this, &Browser::ShowProgressBar);
	connect(ui_->web_view, &QWebEngineView::loadFinished, this, &Browser::HideProgressBar);
	connect(ui_->web_view, &QWebEngineView::urlChanged, this, &Browser::SetUrl);
	connect(ui_->web_view, &QWebEngineView::titleChanged, this, &Browser::SetMyTitle);
	ui_->web_view->load(QUrl("https://www.google.com.ua"));
	ui_->web_view->setContextMenuPolicy(Qt::NoContextMenu);
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
}

void Browser::HideProgressBar()
{
	ui_->load_progress_page->hide();
}
