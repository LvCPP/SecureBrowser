/********************************************************************************
** Form generated from reading UI file 'browser.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSER_H
#define UI_BROWSER_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Browser
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *push_btn_close;
    QHBoxLayout *horizontalLayout;
    QPushButton *push_btn_back;
    QPushButton *push_btn_forward;
    QPushButton *push_btn_reload;
    QPushButton *push_btn_stop;
    QLabel *label;
    QWebEngineView *web_view;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QProgressBar *load_progress_page;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Browser)
    {
        if (Browser->objectName().isEmpty())
            Browser->setObjectName(QStringLiteral("Browser"));
        Browser->resize(755, 594);
        gridLayout = new QGridLayout(Browser);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        push_btn_close = new QPushButton(Browser);
        push_btn_close->setObjectName(QStringLiteral("push_btn_close"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Browser/Resources/closed.ico"), QSize(), QIcon::Normal, QIcon::Off);
        push_btn_close->setIcon(icon);

        horizontalLayout_3->addWidget(push_btn_close);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        push_btn_back = new QPushButton(Browser);
        push_btn_back->setObjectName(QStringLiteral("push_btn_back"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Browser/Resources/Back.png"), QSize(), QIcon::Normal, QIcon::Off);
        push_btn_back->setIcon(icon1);

        horizontalLayout->addWidget(push_btn_back);

        push_btn_forward = new QPushButton(Browser);
        push_btn_forward->setObjectName(QStringLiteral("push_btn_forward"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Browser/Resources/Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        push_btn_forward->setIcon(icon2);

        horizontalLayout->addWidget(push_btn_forward);

        push_btn_reload = new QPushButton(Browser);
        push_btn_reload->setObjectName(QStringLiteral("push_btn_reload"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Browser/Resources/download.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        push_btn_reload->setIcon(icon3);

        horizontalLayout->addWidget(push_btn_reload);

        push_btn_stop = new QPushButton(Browser);
        push_btn_stop->setObjectName(QStringLiteral("push_btn_stop"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Browser/Resources/stop.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        push_btn_stop->setIcon(icon4);

        horizontalLayout->addWidget(push_btn_stop);

        label = new QLabel(Browser);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::StyledPanel);

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout);

        web_view = new QWebEngineView(Browser);
        web_view->setObjectName(QStringLiteral("web_view"));

        verticalLayout->addWidget(web_view);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        load_progress_page = new QProgressBar(Browser);
        load_progress_page->setObjectName(QStringLiteral("load_progress_page"));
        load_progress_page->setStyleSheet(QLatin1String("QProgressBar{\n"
"	text-align:center\n"
"}"));
        load_progress_page->setValue(0);

        horizontalLayout_2->addWidget(load_progress_page);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Browser);

        QMetaObject::connectSlotsByName(Browser);
    } // setupUi

    void retranslateUi(QWidget *Browser)
    {
        Browser->setWindowTitle(QApplication::translate("Browser", "SecureBrowser", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        push_btn_close->setToolTip(QApplication::translate("Browser", "<html><head/><body><p>Close</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        push_btn_close->setText(QString());
#ifndef QT_NO_TOOLTIP
        push_btn_back->setToolTip(QApplication::translate("Browser", "<html><head/><body><p>Back</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        push_btn_back->setWhatsThis(QApplication::translate("Browser", "<html><head/><body><p>Back</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        push_btn_back->setText(QString());
#ifndef QT_NO_TOOLTIP
        push_btn_forward->setToolTip(QApplication::translate("Browser", "<html><head/><body><p>Forward</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        push_btn_forward->setText(QString());
#ifndef QT_NO_TOOLTIP
        push_btn_reload->setToolTip(QApplication::translate("Browser", "<html><head/><body><p>Reload</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        push_btn_reload->setText(QString());
#ifndef QT_NO_TOOLTIP
        push_btn_stop->setToolTip(QApplication::translate("Browser", "<html><head/><body><p>Stop</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        push_btn_stop->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Browser: public Ui_Browser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSER_H
