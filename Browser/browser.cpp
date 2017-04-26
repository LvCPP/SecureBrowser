#include "browser.h"


Browser::Browser(QWidget *parent)
	: QWidget(parent)
{
	ui_->setupUi(this);

	connect(ui_->line_edit_url, &QLineEdit::returnPressed, this, &Browser::SlotEnter);
	connect(ui_->push_btn_back, SIGNAL(clicked()), ui_->web_view, SLOT(back()));
	connect(ui_->push_btn_forward, SIGNAL(clicked()), ui_->web_view, SLOT(forward()));
	connect(ui_->push_btn_refresh, SIGNAL(clicked()), ui_->web_view, SLOT(reload()));
	connect(ui_->push_btn_stop, SIGNAL(clicked()), ui_->web_view, SLOT(stop()));
	connect(ui_->web_view, SIGNAL(loadProgress(int)), ui_->progress_bar, SLOT(setValue(int)));
	connect(ui_->web_view, SIGNAL(linkClicked(Qurl)), this, SLOT(SlotLinkClicked(Qurl)));
}


void Browser::SlotEnter()
{
	ui_->web_view->load(QUrl(ui_->line_edit_url->text()));
	if (!(ui_->line_edit_url->text().startsWith("http://")))
	{
		ui_->web_view->load("http://" + ui_->line_edit_url->text());
	}
}

void Browser::SlotLinkClicked(QUrl url)
{
	ui_->web_view->load(url);
	ui_->line_edit_url->setText(url.toString());
}

