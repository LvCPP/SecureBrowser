#include "browser.h"

Browser::Browser(QWidget *parent)
	: QWidget(parent)
{
	ui->setupUi(this);

	//ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks); //change setLinkDelegationPolicy in QWebEngine
	

	/*ui->webView->load(QUrl("http://google.com"));
	ui->webView->show();	*/

	connect(ui->line_edit_url, &QLineEdit::returnPressed, this, &Browser::slotEnter);
	//connect(ui->webView, &QWebEngineView::linkClicked, this, &Browser::slotLinkClicked); //change &QWebView

	connect(ui->push_btn_back, SIGNAL(clicked()), ui->webView, SLOT(back()));
	connect(ui->push_btn_forward, SIGNAL(clicked()), ui->webView, SLOT(forward()));//Change &QPushButton::clicked;
	connect(ui->push_btn_refresh, SIGNAL(clicked()), ui->webView, SLOT(reload()));
	connect(ui->push_btn_stop, SIGNAL(clicked()), ui->webView, SLOT(stop()));

	/*if (ui->webView->history()->count == 0)
	{
		ui->push_btn_forward->setEnabled(false);	
		ui->push_btn_back->setEnabled(false);
	}*/
}

Browser::~Browser()
{

}

void Browser::slotEnter()
{
	ui->webView->load(QUrl(ui->line_edit_url->text()));
	if (!(ui->line_edit_url->text().startsWith("http://")))
	{
		ui->webView->load("http://" + ui->line_edit_url->text());
	}
	/*if (!(ui->line_edit_url->text().endsWith(".com")))
	{
		ui->webView->load("http://www.google.com/search?sourceid=chrome-psyapi2&ion=1&espv=2&ie=UTF-8&q=" + ui->line_edit_url->text());
	}*/
}

void Browser::slotLinkClicked(QUrl url)
{
	ui->line_edit_url->setText(url.toString());
	ui->webView->load(url);   
	/*
	if(ui->webView->history()->canGoForward())
	{
		ui->push_btn_forward->setEnabled(true);
	}
	else
	{
		ui->push_btn_forward->setEnabled(false)
	}
	
	if(ui->webView->history()->canGoBack())
	{
		ui->push_btn_back->setEnabled(true);
	}
	else
	{
		ui->push_btn_back->setEnabled(false)
	}
	*/
}

