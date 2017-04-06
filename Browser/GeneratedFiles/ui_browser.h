/********************************************************************************
** Form generated from reading UI file 'browser.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSER_H
#define UI_BROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BrowserClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BrowserClass)
    {
        if (BrowserClass->objectName().isEmpty())
            BrowserClass->setObjectName(QStringLiteral("BrowserClass"));
        BrowserClass->resize(600, 400);
        menuBar = new QMenuBar(BrowserClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BrowserClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BrowserClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BrowserClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BrowserClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BrowserClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BrowserClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BrowserClass->setStatusBar(statusBar);

        retranslateUi(BrowserClass);

        QMetaObject::connectSlotsByName(BrowserClass);
    } // setupUi

    void retranslateUi(QMainWindow *BrowserClass)
    {
        BrowserClass->setWindowTitle(QApplication::translate("BrowserClass", "Browser", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BrowserClass: public Ui_BrowserClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSER_H
