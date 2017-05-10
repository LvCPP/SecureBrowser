#pragma once

#include <QWidget>

namespace Ui 
{ 
class Browser; 
}

namespace SecureBrowser
{

class Browser : public QWidget
{
	Q_OBJECT

public:
	Browser(QWidget *parent = 0);
	~Browser();

private slots:
	void SlotEnter();       // For Enter in LineEdit
	void SetUrl(const QUrl &url); // For clicked URL

private:
	QScopedPointer<Ui::Browser> ui_;
};

}