#include "browser.h"
#include "ui_browser.h"

using namespace SecureBrowser;

Browser::Browser(QWidget *parent)
	: QWidget(parent)
	, ui_(new Ui::Browser())
{
	ui_->setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	connect(ui_->line_edit, &QLineEdit::returnPressed, this, &Browser::SlotEnter);
	connect(ui_->push_btn_back, &QPushButton::clicked, ui_->web_view, &QWebEngineView::back);
	connect(ui_->push_btn_forward, &QPushButton::clicked, ui_->web_view, &QWebEngineView::forward);
	connect(ui_->push_btn_reload, &QPushButton::clicked, ui_->web_view, &QWebEngineView::reload);
	connect(ui_->push_btn_stop, &QPushButton::clicked, ui_->web_view, &QWebEngineView::stop);
	connect(ui_->web_view, &QWebEngineView::loadProgress, ui_->load_progress_page, &QProgressBar::setValue);
	connect(ui_->web_view, &QWebEngineView::urlChanged, this, &Browser::SetUrl);
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
