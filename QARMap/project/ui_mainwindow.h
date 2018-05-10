/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionOpenView;
    QAction *actionCloseView;
    QAction *actionPauseView;
    QAction *actionUnpauseView;
    QAction *actionWeatherSetting;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionCameraControl;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QWebEngineView *webView;
    QListWidget *listWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1108, 686);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionOpenView = new QAction(MainWindow);
        actionOpenView->setObjectName(QStringLiteral("actionOpenView"));
        actionCloseView = new QAction(MainWindow);
        actionCloseView->setObjectName(QStringLiteral("actionCloseView"));
        actionPauseView = new QAction(MainWindow);
        actionPauseView->setObjectName(QStringLiteral("actionPauseView"));
        actionUnpauseView = new QAction(MainWindow);
        actionUnpauseView->setObjectName(QStringLiteral("actionUnpauseView"));
        actionWeatherSetting = new QAction(MainWindow);
        actionWeatherSetting->setObjectName(QStringLiteral("actionWeatherSetting"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCameraControl = new QAction(MainWindow);
        actionCameraControl->setObjectName(QStringLiteral("actionCameraControl"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        webView = new QWebEngineView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));

        horizontalLayout->addWidget(webView);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout->addWidget(listWidget);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"	border-image: url(:/background.png);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(661, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QLatin1String("#widget_2{\n"
"	border-image: url(:/CA.png);\n"
"}"));

        horizontalLayout_2->addWidget(widget_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setStyleSheet(QLatin1String("QStatusBar::item{\n"
"	border: 0px;\n"
"}"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Alt+Q", 0));
        actionOpenView->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
        actionCloseView->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        actionPauseView->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", 0));
        actionUnpauseView->setText(QApplication::translate("MainWindow", "\347\273\247\347\273\255", 0));
        actionWeatherSetting->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\345\244\251\346\260\224", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
        actionHelp->setShortcut(QApplication::translate("MainWindow", "F1", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "?", 0));
        actionCameraControl->setText(QApplication::translate("MainWindow", "\347\233\221\350\247\206\347\233\270\346\234\272\346\216\247\345\210\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
