/********************************************************************************
** Form generated from reading UI file 'addTask.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTASK_H
#define UI_ADDTASK_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_Once;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButton_Repeat;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioButton_Deadline;
    QLabel *label;
    QGroupBox *groupBox_2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *radioButton_3;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout;
    QLabel *ToDo;
    QPlainTextEdit *plainTextEdit_NameOfTask;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_accept;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *Task)
    {
        if (Task->objectName().isEmpty())
            Task->setObjectName("Task");
        Task->resize(508, 391);
        groupBox = new QGroupBox(Task);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 100, 381, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font.setBold(true);
        groupBox->setFont(font);
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 20, 341, 22));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_Once = new QRadioButton(widget);
        radioButton_Once->setObjectName("radioButton_Once");

        horizontalLayout_2->addWidget(radioButton_Once);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        radioButton_Repeat = new QRadioButton(widget);
        radioButton_Repeat->setObjectName("radioButton_Repeat");

        horizontalLayout_2->addWidget(radioButton_Repeat);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        radioButton_Deadline = new QRadioButton(widget);
        radioButton_Deadline->setObjectName("radioButton_Deadline");

        horizontalLayout_2->addWidget(radioButton_Deadline);

        label = new QLabel(Task);
        label->setObjectName("label");
        label->setGeometry(QRect(49, 182, 31, 20));
        groupBox_2 = new QGroupBox(Task);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(40, 150, 381, 51));
        groupBox_2->setFont(font);
        widget1 = new QWidget(groupBox_2);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 20, 321, 22));
        horizontalLayout_3 = new QHBoxLayout(widget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(widget1);
        radioButton->setObjectName("radioButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-red-circle-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton->setIcon(icon);

        horizontalLayout_3->addWidget(radioButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        radioButton_2 = new QRadioButton(widget1);
        radioButton_2->setObjectName("radioButton_2");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-yellow-circle-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_2->setIcon(icon1);

        horizontalLayout_3->addWidget(radioButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        radioButton_3 = new QRadioButton(widget1);
        radioButton_3->setObjectName("radioButton_3");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-green-67.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_3->setIcon(icon2);

        horizontalLayout_3->addWidget(radioButton_3);

        widget2 = new QWidget(Task);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(40, 10, 381, 81));
        horizontalLayout = new QHBoxLayout(widget2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ToDo = new QLabel(widget2);
        ToDo->setObjectName("ToDo");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font1.setPointSize(11);
        font1.setBold(true);
        ToDo->setFont(font1);

        horizontalLayout->addWidget(ToDo);

        plainTextEdit_NameOfTask = new QPlainTextEdit(widget2);
        plainTextEdit_NameOfTask->setObjectName("plainTextEdit_NameOfTask");

        horizontalLayout->addWidget(plainTextEdit_NameOfTask);

        widget3 = new QWidget(Task);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(310, 350, 171, 21));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_accept = new QPushButton(widget3);
        pushButton_accept->setObjectName("pushButton_accept");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/widgets_icons/checkmark-verify-interface-symbol-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_accept->setIcon(icon3);

        horizontalLayout_4->addWidget(pushButton_accept);

        pushButton_cancel = new QPushButton(widget3);
        pushButton_cancel->setObjectName("pushButton_cancel");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/widgets_icons/close-circular-button-symbol.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cancel->setIcon(icon4);

        horizontalLayout_4->addWidget(pushButton_cancel);


        retranslateUi(Task);

        QMetaObject::connectSlotsByName(Task);
    } // setupUi

    void retranslateUi(QDialog *Task)
    {
        Task->setWindowTitle(QCoreApplication::translate("Task", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Task", "\344\272\213\344\273\266\347\261\273\345\236\213", nullptr));
        radioButton_Once->setText(QCoreApplication::translate("Task", "\345\215\225\346\254\241", nullptr));
        radioButton_Repeat->setText(QCoreApplication::translate("Task", "\351\207\215\345\244\215\345\236\213", nullptr));
        radioButton_Deadline->setText(QCoreApplication::translate("Task", "\346\227\245\346\234\237\346\210\252\346\255\242\345\236\213", nullptr));
        label->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("Task", "\344\272\213\344\273\266\344\274\230\345\205\210\347\272\247", nullptr));
        radioButton->setText(QCoreApplication::translate("Task", "\351\253\230", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Task", "\344\270\255", nullptr));
        radioButton_3->setText(QCoreApplication::translate("Task", "\344\275\216", nullptr));
        ToDo->setText(QCoreApplication::translate("Task", "\350\256\241\345\210\222", nullptr));
        plainTextEdit_NameOfTask->setPlainText(QCoreApplication::translate("Task", "\350\257\267\350\276\223\345\205\245\345\205\267\344\275\223\347\232\204\344\272\213\351\241\271", nullptr));
        pushButton_accept->setText(QCoreApplication::translate("Task", "\347\241\256\345\256\232", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("Task", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Task: public Ui_Task {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTASK_H
