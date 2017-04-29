#include "browser.h"


Browser::Browser(QWidget *parent)
	: QWidget(parent), ui_(std::make_unique<Ui::BrowserClass>())
{
	ui_->setupUi(this);
	connect(ui_->line_edit_url, &QLineEdit::returnPressed, this, &Browser::SlotEnter);
	connect(ui_->push_btn_back, &QPushButton::clicked, ui_->web_view, &QWebEngineView::back);
	connect(ui_->push_btn_forward, &QPushButton::clicked, ui_->web_view, &QWebEngineView::forward);
	connect(ui_->push_btn_refresh, &QPushButton::clicked, ui_->web_view, &QWebEngineView::reload);
	connect(ui_->push_btn_stop, &QPushButton::clicked, ui_->web_view, &QWebEngineView::stop);
	connect(ui_->web_view, &QWebEngineView::loadProgress, ui_->progress_bar, &QProgressBar::setValue);
	connect(ui_->web_view, &QWebEngineView::urlChanged, this, &Browser::SetUrl);
}


void Browser::SlotEnter()
{
	QString uri = ui_->line_edit_url->text();
	if (!(uri.startsWith("http://")))
	{
		uri = "http://" + uri;
	}
	ui_->web_view->load(uri);
}


void Browser::SetUrl(const QUrl &url)
{
	ui_->line_edit_url->setText(url.toString());
}




