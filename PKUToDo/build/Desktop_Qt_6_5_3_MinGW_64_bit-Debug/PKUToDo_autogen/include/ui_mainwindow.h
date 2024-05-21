/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_home;
    QWidget *tab_calendar;
    QWidget *tab_toDo;
    QWidget *tab_schedule;
    QWidget *tab_statistics;
    QWidget *tab_settings;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuPKUToDo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(683, 496);
        MainWindow->setContextMenuPolicy(Qt::PreventContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/widgets_icons/check-sign-in-a-rounded-black-square.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab_home = new QWidget();
        tab_home->setObjectName("tab_home");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/widgets_icons/house-outline.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_home, icon1, QString());
        tab_calendar = new QWidget();
        tab_calendar->setObjectName("tab_calendar");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-calendar-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_calendar, icon2, QString());
        tab_toDo = new QWidget();
        tab_toDo->setObjectName("tab_toDo");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/widgets_icons/checked.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_toDo, icon3, QString());
        tab_schedule = new QWidget();
        tab_schedule->setObjectName("tab_schedule");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/widgets_icons/list (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_schedule, icon4, QString());
        tab_statistics = new QWidget();
        tab_statistics->setObjectName("tab_statistics");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/widgets_icons/statistic-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_statistics, icon5, QString());
        tab_settings = new QWidget();
        tab_settings->setObjectName("tab_settings");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-setting-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_settings, icon6, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 683, 17));
        menuPKUToDo = new QMenu(menubar);
        menuPKUToDo->setObjectName("menuPKUToDo");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuPKUToDo->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PKUToDo1.0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_home), QCoreApplication::translate("MainWindow", "\344\270\273\351\241\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_calendar), QCoreApplication::translate("MainWindow", "\346\227\245\345\216\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_toDo), QCoreApplication::translate("MainWindow", "\344\273\243\345\212\236", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_schedule), QCoreApplication::translate("MainWindow", "\344\270\223\346\263\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_statistics), QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\273\237\350\256\241", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_settings), QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        menuPKUToDo->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
