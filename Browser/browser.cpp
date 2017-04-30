#include "browser.h"

using namespace SecureBrowser;

Browser::Browser(QWidget *parent)
	: QWidget(parent), ui_(std::make_unique<Ui::BrowserClass>())
{
	ui_->setupUi(this);
	connect(ui_->LineEdit, &QLineEdit::returnPressed, this, &Browser::SlotEnter);
	connect(ui_->BtnBack, &QPushButton::clicked, ui_->WebView, &QWebEngineView::back);
	connect(ui_->BtnForward, &QPushButton::clicked, ui_->WebView, &QWebEngineView::forward);
	connect(ui_->BtnReload, &QPushButton::clicked, ui_->WebView, &QWebEngineView::reload);
	connect(ui_->BtnStop, &QPushButton::clicked, ui_->WebView, &QWebEngineView::stop);
	connect(ui_->WebView, &QWebEngineView::loadProgress, ui_->ProgressBar, &QProgressBar::setValue);
	connect(ui_->WebView, &QWebEngineView::urlChanged, this, &Browser::SetUrl);
}

void Browser::SlotEnter()
{
	QString uri = ui_->LineEdit->text();
	if (!(uri.startsWith("http://")))
	{
		uri = "http://" + uri;
	}
	ui_->WebView->load(uri);
}

void Browser::SetUrl(const QUrl &url)
{
	ui_->LineEdit->setText(url.toString());
}
