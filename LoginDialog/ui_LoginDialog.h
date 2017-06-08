/********************************************************************************
** Form generated from reading UI file 'LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWizard>
#include <QtWidgets/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_Wizard
{
public:
    QWizardPage *welcome_page;
    QLabel *welcome_background_label;
    QWizardPage *login_page;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *top_label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *username_label;
    QLineEdit *username_lineedit;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QLabel *password_label;
    QLineEdit *password_lineedit;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_25;
    QCheckBox *agree_checkbox;
    QLabel *agree_label;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *login_button;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_4;
    QWizardPage *make_photo_page;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *camera_select_label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *camera_select_combobox;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_11;
    QLabel *image_label;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *take_photo_button;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *accept_photo_button;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *decline_photo_button;
    QSpacerItem *horizontalSpacer_18;
    QWizardPage *last_page;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_9;
    QLabel *last_page_label;
    QSpacerItem *verticalSpacer_10;

    void setupUi(QWizard *Wizard)
    {
        if (Wizard->objectName().isEmpty())
            Wizard->setObjectName(QStringLiteral("Wizard"));
        Wizard->resize(446, 472);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Wizard->sizePolicy().hasHeightForWidth());
        Wizard->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        Wizard->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/sb.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Wizard->setWindowIcon(icon);
        Wizard->setWizardStyle(QWizard::ModernStyle);
        Wizard->setOptions(QWizard::NoCancelButtonOnLastPage);
        welcome_page = new QWizardPage();
        welcome_page->setObjectName(QStringLiteral("welcome_page"));
        QFont font1;
        font1.setPointSize(12);
        welcome_page->setFont(font1);
        welcome_background_label = new QLabel(welcome_page);
        welcome_background_label->setObjectName(QStringLiteral("welcome_background_label"));
        welcome_background_label->setGeometry(QRect(0, 0, 446, 427));
        welcome_background_label->setStyleSheet(QStringLiteral("background-image: url(:/Resources/intro_background.jpg);"));
        welcome_background_label->setPixmap(QPixmap(QString::fromUtf8(":/Resources/intro_background.jpg")));
        welcome_background_label->setScaledContents(true);
        welcome_background_label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        welcome_background_label->setTextInteractionFlags(Qt::NoTextInteraction);
        Wizard->setPage(0, welcome_page);
        login_page = new QWizardPage();
        login_page->setObjectName(QStringLiteral("login_page"));
        gridLayout = new QGridLayout(login_page);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        top_label = new QLabel(login_page);
        top_label->setObjectName(QStringLiteral("top_label"));
        top_label->setFont(font);
        top_label->setTextFormat(Qt::RichText);
        top_label->setScaledContents(true);
        top_label->setAlignment(Qt::AlignCenter);
        top_label->setWordWrap(true);
        top_label->setMargin(0);
        top_label->setIndent(-1);
        top_label->setOpenExternalLinks(false);

        verticalLayout->addWidget(top_label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        username_label = new QLabel(login_page);
        username_label->setObjectName(QStringLiteral("username_label"));
        username_label->setFont(font);
        username_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        username_label->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_2->addWidget(username_label);

        username_lineedit = new QLineEdit(login_page);
        username_lineedit->setObjectName(QStringLiteral("username_lineedit"));
        username_lineedit->setFont(font);

        horizontalLayout_2->addWidget(username_lineedit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        password_label = new QLabel(login_page);
        password_label->setObjectName(QStringLiteral("password_label"));
        password_label->setFont(font);
        password_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        password_label->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_3->addWidget(password_label);

        password_lineedit = new QLineEdit(login_page);
        password_lineedit->setObjectName(QStringLiteral("password_lineedit"));
        password_lineedit->setFont(font);
        password_lineedit->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(password_lineedit);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_25);

        agree_checkbox = new QCheckBox(login_page);
        agree_checkbox->setObjectName(QStringLiteral("agree_checkbox"));
        agree_checkbox->setLayoutDirection(Qt::RightToLeft);
        agree_checkbox->setCheckable(true);
        agree_checkbox->setTristate(false);

        horizontalLayout_9->addWidget(agree_checkbox);

        agree_label = new QLabel(login_page);
        agree_label->setObjectName(QStringLiteral("agree_label"));
        agree_label->setTextFormat(Qt::RichText);
        agree_label->setOpenExternalLinks(true);

        horizontalLayout_9->addWidget(agree_label);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_26);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_3 = new QSpacerItem(414, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        login_button = new QPushButton(login_page);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setFont(font);
        login_button->setAutoDefault(true);
        login_button->setFlat(false);

        horizontalLayout_4->addWidget(login_button);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_6 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        Wizard->setPage(1, login_page);
        make_photo_page = new QWizardPage();
        make_photo_page->setObjectName(QStringLiteral("make_photo_page"));
        gridLayout_2 = new QGridLayout(make_photo_page);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(21, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        camera_select_label = new QLabel(make_photo_page);
        camera_select_label->setObjectName(QStringLiteral("camera_select_label"));
        camera_select_label->setTextFormat(Qt::RichText);
        camera_select_label->setScaledContents(false);
        camera_select_label->setAlignment(Qt::AlignCenter);
        camera_select_label->setWordWrap(false);

        horizontalLayout_5->addWidget(camera_select_label);

        horizontalSpacer_2 = new QSpacerItem(22, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_5 = new QSpacerItem(13, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        camera_select_combobox = new QComboBox(make_photo_page);
        camera_select_combobox->setObjectName(QStringLiteral("camera_select_combobox"));
        sizePolicy.setHeightForWidth(camera_select_combobox->sizePolicy().hasHeightForWidth());
        camera_select_combobox->setSizePolicy(sizePolicy);
        camera_select_combobox->setMinimumSize(QSize(380, 22));
        camera_select_combobox->setMaximumSize(QSize(380, 22));
        camera_select_combobox->setBaseSize(QSize(380, 22));
        camera_select_combobox->setMinimumContentsLength(0);
        camera_select_combobox->setDuplicatesEnabled(true);
        camera_select_combobox->setModelColumn(0);

        horizontalLayout_6->addWidget(camera_select_combobox);

        horizontalSpacer_8 = new QSpacerItem(13, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_11 = new QSpacerItem(13, 297, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        image_label = new QLabel(make_photo_page);
        image_label->setObjectName(QStringLiteral("image_label"));
        sizePolicy.setHeightForWidth(image_label->sizePolicy().hasHeightForWidth());
        image_label->setSizePolicy(sizePolicy);
        image_label->setMinimumSize(QSize(400, 300));
        image_label->setMaximumSize(QSize(400, 300));
        image_label->setBaseSize(QSize(400, 300));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial Narrow"));
        image_label->setFont(font2);
        image_label->setFrameShape(QFrame::StyledPanel);
        image_label->setScaledContents(true);
        image_label->setAlignment(Qt::AlignCenter);
        image_label->setIndent(10);

        horizontalLayout_7->addWidget(image_label);

        horizontalSpacer_12 = new QSpacerItem(13, 294, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        take_photo_button = new QPushButton(make_photo_page);
        take_photo_button->setObjectName(QStringLiteral("take_photo_button"));
        take_photo_button->setEnabled(true);
        sizePolicy.setHeightForWidth(take_photo_button->sizePolicy().hasHeightForWidth());
        take_photo_button->setSizePolicy(sizePolicy);
        take_photo_button->setMinimumSize(QSize(90, 23));
        take_photo_button->setMaximumSize(QSize(90, 23));

        horizontalLayout_8->addWidget(take_photo_button);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);

        accept_photo_button = new QPushButton(make_photo_page);
        accept_photo_button->setObjectName(QStringLiteral("accept_photo_button"));
        accept_photo_button->setEnabled(false);
        sizePolicy.setHeightForWidth(accept_photo_button->sizePolicy().hasHeightForWidth());
        accept_photo_button->setSizePolicy(sizePolicy);
        accept_photo_button->setMinimumSize(QSize(90, 23));
        accept_photo_button->setMaximumSize(QSize(90, 23));

        horizontalLayout_8->addWidget(accept_photo_button);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        decline_photo_button = new QPushButton(make_photo_page);
        decline_photo_button->setObjectName(QStringLiteral("decline_photo_button"));
        decline_photo_button->setEnabled(false);
        sizePolicy.setHeightForWidth(decline_photo_button->sizePolicy().hasHeightForWidth());
        decline_photo_button->setSizePolicy(sizePolicy);
        decline_photo_button->setMinimumSize(QSize(90, 23));
        decline_photo_button->setMaximumSize(QSize(90, 23));

        horizontalLayout_8->addWidget(decline_photo_button);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);


        verticalLayout_2->addLayout(horizontalLayout_8);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        Wizard->setPage(2, make_photo_page);
        last_page = new QWizardPage();
        last_page->setObjectName(QStringLiteral("last_page"));
        gridLayout_3 = new QGridLayout(last_page);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_9);

        last_page_label = new QLabel(last_page);
        last_page_label->setObjectName(QStringLiteral("last_page_label"));
        last_page_label->setLayoutDirection(Qt::LeftToRight);
        last_page_label->setInputMethodHints(Qt::ImhNone);
        last_page_label->setTextFormat(Qt::RichText);
        last_page_label->setScaledContents(false);
        last_page_label->setAlignment(Qt::AlignCenter);
        last_page_label->setWordWrap(true);
        last_page_label->setMargin(20);

        verticalLayout_3->addWidget(last_page_label);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_10);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);

        Wizard->setPage(3, last_page);

        retranslateUi(Wizard);

        login_button->setDefault(false);


        QMetaObject::connectSlotsByName(Wizard);
    } // setupUi

    void retranslateUi(QWizard *Wizard)
    {
        Wizard->setWindowTitle(QApplication::translate("Wizard", "SecureBrowser authentication wizard", Q_NULLPTR));
        welcome_background_label->setText(QString());
        login_page->setTitle(QString());
        login_page->setSubTitle(QString());
        top_label->setText(QApplication::translate("Wizard", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">You are invited to pass </span><span style=\" font-size:10pt; font-weight:600;\">Technical test</span><span style=\" font-size:10pt;\"> as one of the stages to be enrolled in SoftServe IT Academy. Please input your credentials:</span></p></body></html>", Q_NULLPTR));
        username_label->setText(QApplication::translate("Wizard", "Username*", Q_NULLPTR));
        password_label->setText(QApplication::translate("Wizard", "Password*", Q_NULLPTR));
        agree_checkbox->setText(QString());
        agree_label->setText(QApplication::translate("Wizard", "<html><head/><body><p><span style=\" font-size:10pt;\">I agree to </span><a href=\"https://drive.google.com/open?id=0B9Xa2M9s3StoOFNXYXQ2QWZPZ28\"><span style=\" font-size:10pt; text-decoration: underline; color:#0000ff;\">The Terms of Service and Privacy Notes</span></a></p></body></html>", Q_NULLPTR));
        login_button->setText(QApplication::translate("Wizard", "Login", Q_NULLPTR));
        camera_select_label->setText(QApplication::translate("Wizard", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt;\">Please select your camera for face and ID detection:</span></p></body></html>", Q_NULLPTR));
        image_label->setText(QString());
        take_photo_button->setText(QApplication::translate("Wizard", "Take photo", Q_NULLPTR));
        accept_photo_button->setText(QApplication::translate("Wizard", "Save photo", Q_NULLPTR));
        decline_photo_button->setText(QApplication::translate("Wizard", "Decline photo", Q_NULLPTR));
        last_page_label->setText(QApplication::translate("Wizard", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">You have finished the authentication process. Please get ready for the test!</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Wizard: public Ui_Wizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
