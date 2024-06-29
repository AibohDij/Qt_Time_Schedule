/********************************************************************************
** Form generated from reading UI file 'task.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_H
#define UI_TASK_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_14;
    QPlainTextEdit *plainTextEdit_Name;
    QLabel *ToDo_2;
    QPlainTextEdit *plainTextEdit_Details;
    QLabel *ToDo;
    QGroupBox *groupBox_type;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_Once;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButton_Repeat;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioButton_Deadline;
    QGroupBox *groupBox_priority;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_high;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *radioButton_medium;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *radioButton_low;
    QStackedWidget *stackedWidget_types;
    QWidget *page_Once;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_start;
    QDateTimeEdit *dateTimeEdit_start_once;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_end;
    QDateTimeEdit *dateTimeEdit_end_once;
    QSpacerItem *horizontalSpacer_8;
    QWidget *page_Repeat;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_startDate;
    QDateEdit *dateEdit_start_repeat;
    QLabel *label_endDate;
    QDateEdit *dateEdit_end_repeat;
    QLabel *label_start_5;
    QTimeEdit *timeEdit_start_repeat;
    QLabel *label_start_6;
    QTimeEdit *timeEdit_end_repeat;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_everyDay;
    QCheckBox *checkBox_Monday;
    QCheckBox *checkBox_TuesDay;
    QCheckBox *checkBox_Wednesday;
    QCheckBox *checkBox_Thursday;
    QCheckBox *checkBox_Friday;
    QCheckBox *checkBox_Saturday;
    QCheckBox *checkBox_Sunday;
    QWidget *page_Deadline;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_end_deadline;
    QDateTimeEdit *dateTimeEdit_deadline;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_accept;
    QPushButton *pushButton_cancel;
    QLabel *label;

    void setupUi(QDialog *Task)
    {
        if (Task->objectName().isEmpty())
            Task->setObjectName("Task");
        Task->resize(600, 466);
        Task->setMinimumSize(QSize(600, 400));
        QFont font;
        font.setPointSize(11);
        Task->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/widgets_icons/document.png"), QSize(), QIcon::Normal, QIcon::Off);
        Task->setWindowIcon(icon);
        verticalLayout_3 = new QVBoxLayout(Task);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 0, 3, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_14, 1, 4, 1, 1);

        plainTextEdit_Name = new QPlainTextEdit(Task);
        plainTextEdit_Name->setObjectName("plainTextEdit_Name");
        plainTextEdit_Name->setMaximumSize(QSize(16777215, 100));

        gridLayout_2->addWidget(plainTextEdit_Name, 0, 2, 1, 1);

        ToDo_2 = new QLabel(Task);
        ToDo_2->setObjectName("ToDo_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font1.setPointSize(13);
        font1.setBold(true);
        ToDo_2->setFont(font1);

        gridLayout_2->addWidget(ToDo_2, 1, 0, 1, 1);

        plainTextEdit_Details = new QPlainTextEdit(Task);
        plainTextEdit_Details->setObjectName("plainTextEdit_Details");
        plainTextEdit_Details->setMinimumSize(QSize(0, 70));
        plainTextEdit_Details->setMaximumSize(QSize(100000, 300));
        plainTextEdit_Details->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        gridLayout_2->addWidget(plainTextEdit_Details, 1, 1, 1, 3);

        ToDo = new QLabel(Task);
        ToDo->setObjectName("ToDo");
        ToDo->setFont(font1);

        gridLayout_2->addWidget(ToDo, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        groupBox_type = new QGroupBox(Task);
        groupBox_type->setObjectName("groupBox_type");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_type->sizePolicy().hasHeightForWidth());
        groupBox_type->setSizePolicy(sizePolicy);
        groupBox_type->setMinimumSize(QSize(0, 80));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font2.setPointSize(11);
        font2.setBold(true);
        groupBox_type->setFont(font2);
        horizontalLayout_5 = new QHBoxLayout(groupBox_type);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioButton_Once = new QRadioButton(groupBox_type);
        radioButton_Once->setObjectName("radioButton_Once");
        radioButton_Once->setFont(font2);
        radioButton_Once->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_Once);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        radioButton_Repeat = new QRadioButton(groupBox_type);
        radioButton_Repeat->setObjectName("radioButton_Repeat");

        horizontalLayout_2->addWidget(radioButton_Repeat);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        radioButton_Deadline = new QRadioButton(groupBox_type);
        radioButton_Deadline->setObjectName("radioButton_Deadline");

        horizontalLayout_2->addWidget(radioButton_Deadline);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox_type);

        groupBox_priority = new QGroupBox(Task);
        groupBox_priority->setObjectName("groupBox_priority");
        sizePolicy.setHeightForWidth(groupBox_priority->sizePolicy().hasHeightForWidth());
        groupBox_priority->setSizePolicy(sizePolicy);
        groupBox_priority->setMinimumSize(QSize(0, 80));
        groupBox_priority->setFont(font2);
        horizontalLayout_6 = new QHBoxLayout(groupBox_priority);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        radioButton_high = new QRadioButton(groupBox_priority);
        radioButton_high->setObjectName("radioButton_high");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-red-circle-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_high->setIcon(icon1);

        horizontalLayout_3->addWidget(radioButton_high);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        radioButton_medium = new QRadioButton(groupBox_priority);
        radioButton_medium->setObjectName("radioButton_medium");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-yellow-circle-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_medium->setIcon(icon2);

        horizontalLayout_3->addWidget(radioButton_medium);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        radioButton_low = new QRadioButton(groupBox_priority);
        radioButton_low->setObjectName("radioButton_low");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/widgets_icons/icons8-green-67.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_low->setIcon(icon3);
        radioButton_low->setChecked(true);

        horizontalLayout_3->addWidget(radioButton_low);


        horizontalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox_priority);

        stackedWidget_types = new QStackedWidget(Task);
        stackedWidget_types->setObjectName("stackedWidget_types");
        stackedWidget_types->setMinimumSize(QSize(0, 130));
        page_Once = new QWidget();
        page_Once->setObjectName("page_Once");
        horizontalLayout_7 = new QHBoxLayout(page_Once);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_7 = new QSpacerItem(56, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        label_start = new QLabel(page_Once);
        label_start->setObjectName("label_start");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font3.setPointSize(10);
        font3.setBold(true);
        label_start->setFont(font3);

        horizontalLayout_7->addWidget(label_start);

        dateTimeEdit_start_once = new QDateTimeEdit(page_Once);
        dateTimeEdit_start_once->setObjectName("dateTimeEdit_start_once");
        dateTimeEdit_start_once->setCalendarPopup(true);

        horizontalLayout_7->addWidget(dateTimeEdit_start_once);

        horizontalSpacer_6 = new QSpacerItem(57, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        label_end = new QLabel(page_Once);
        label_end->setObjectName("label_end");
        label_end->setFont(font3);

        horizontalLayout_7->addWidget(label_end);

        dateTimeEdit_end_once = new QDateTimeEdit(page_Once);
        dateTimeEdit_end_once->setObjectName("dateTimeEdit_end_once");
        dateTimeEdit_end_once->setCalendarPopup(true);

        horizontalLayout_7->addWidget(dateTimeEdit_end_once);

        horizontalSpacer_8 = new QSpacerItem(56, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        stackedWidget_types->addWidget(page_Once);
        page_Repeat = new QWidget();
        page_Repeat->setObjectName("page_Repeat");
        verticalLayout_2 = new QVBoxLayout(page_Repeat);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_startDate = new QLabel(page_Repeat);
        label_startDate->setObjectName("label_startDate");
        label_startDate->setFont(font3);

        horizontalLayout_8->addWidget(label_startDate);

        dateEdit_start_repeat = new QDateEdit(page_Repeat);
        dateEdit_start_repeat->setObjectName("dateEdit_start_repeat");
        dateEdit_start_repeat->setCalendarPopup(true);

        horizontalLayout_8->addWidget(dateEdit_start_repeat);

        label_endDate = new QLabel(page_Repeat);
        label_endDate->setObjectName("label_endDate");
        label_endDate->setFont(font3);

        horizontalLayout_8->addWidget(label_endDate);

        dateEdit_end_repeat = new QDateEdit(page_Repeat);
        dateEdit_end_repeat->setObjectName("dateEdit_end_repeat");
        dateEdit_end_repeat->setCalendarPopup(true);

        horizontalLayout_8->addWidget(dateEdit_end_repeat);

        label_start_5 = new QLabel(page_Repeat);
        label_start_5->setObjectName("label_start_5");
        label_start_5->setFont(font3);

        horizontalLayout_8->addWidget(label_start_5);

        timeEdit_start_repeat = new QTimeEdit(page_Repeat);
        timeEdit_start_repeat->setObjectName("timeEdit_start_repeat");

        horizontalLayout_8->addWidget(timeEdit_start_repeat);

        label_start_6 = new QLabel(page_Repeat);
        label_start_6->setObjectName("label_start_6");
        label_start_6->setFont(font3);

        horizontalLayout_8->addWidget(label_start_6);

        timeEdit_end_repeat = new QTimeEdit(page_Repeat);
        timeEdit_end_repeat->setObjectName("timeEdit_end_repeat");

        horizontalLayout_8->addWidget(timeEdit_end_repeat);


        verticalLayout_2->addLayout(horizontalLayout_8);

        groupBox = new QGroupBox(page_Repeat);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 60));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        checkBox_everyDay = new QCheckBox(groupBox);
        checkBox_everyDay->setObjectName("checkBox_everyDay");
        checkBox_everyDay->setChecked(false);

        gridLayout->addWidget(checkBox_everyDay, 0, 0, 1, 1);

        checkBox_Monday = new QCheckBox(groupBox);
        checkBox_Monday->setObjectName("checkBox_Monday");

        gridLayout->addWidget(checkBox_Monday, 0, 1, 1, 1);

        checkBox_TuesDay = new QCheckBox(groupBox);
        checkBox_TuesDay->setObjectName("checkBox_TuesDay");

        gridLayout->addWidget(checkBox_TuesDay, 0, 2, 1, 1);

        checkBox_Wednesday = new QCheckBox(groupBox);
        checkBox_Wednesday->setObjectName("checkBox_Wednesday");

        gridLayout->addWidget(checkBox_Wednesday, 0, 3, 1, 1);

        checkBox_Thursday = new QCheckBox(groupBox);
        checkBox_Thursday->setObjectName("checkBox_Thursday");

        gridLayout->addWidget(checkBox_Thursday, 1, 0, 1, 1);

        checkBox_Friday = new QCheckBox(groupBox);
        checkBox_Friday->setObjectName("checkBox_Friday");

        gridLayout->addWidget(checkBox_Friday, 1, 1, 1, 1);

        checkBox_Saturday = new QCheckBox(groupBox);
        checkBox_Saturday->setObjectName("checkBox_Saturday");

        gridLayout->addWidget(checkBox_Saturday, 1, 2, 1, 1);

        checkBox_Sunday = new QCheckBox(groupBox);
        checkBox_Sunday->setObjectName("checkBox_Sunday");

        gridLayout->addWidget(checkBox_Sunday, 1, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        stackedWidget_types->addWidget(page_Repeat);
        page_Deadline = new QWidget();
        page_Deadline->setObjectName("page_Deadline");
        horizontalLayout_9 = new QHBoxLayout(page_Deadline);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_9 = new QSpacerItem(161, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        label_end_deadline = new QLabel(page_Deadline);
        label_end_deadline->setObjectName("label_end_deadline");
        label_end_deadline->setFont(font3);

        horizontalLayout_9->addWidget(label_end_deadline);

        dateTimeEdit_deadline = new QDateTimeEdit(page_Deadline);
        dateTimeEdit_deadline->setObjectName("dateTimeEdit_deadline");
        dateTimeEdit_deadline->setCalendarPopup(true);

        horizontalLayout_9->addWidget(dateTimeEdit_deadline);

        horizontalSpacer_11 = new QSpacerItem(160, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_11);

        stackedWidget_types->addWidget(page_Deadline);

        verticalLayout->addWidget(stackedWidget_types);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pushButton_accept = new QPushButton(Task);
        pushButton_accept->setObjectName("pushButton_accept");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/widgets_icons/checkmark-verify-interface-symbol-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_accept->setIcon(icon4);

        horizontalLayout_4->addWidget(pushButton_accept);

        pushButton_cancel = new QPushButton(Task);
        pushButton_cancel->setObjectName("pushButton_cancel");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/widgets_icons/close-circular-button-symbol.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cancel->setIcon(icon5);

        horizontalLayout_4->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout);

        label = new QLabel(Task);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);


        retranslateUi(Task);

        stackedWidget_types->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Task);
    } // setupUi

    void retranslateUi(QDialog *Task)
    {
        Task->setWindowTitle(QCoreApplication::translate("Task", "add/modifyTask", nullptr));
        ToDo_2->setText(QCoreApplication::translate("Task", "\345\205\267\344\275\223\345\206\205\345\256\271", nullptr));
        plainTextEdit_Details->setPlainText(QCoreApplication::translate("Task", "\350\257\267\350\276\223\345\205\245\345\205\267\344\275\223\347\232\204\347\273\206\350\212\202", nullptr));
        ToDo->setText(QCoreApplication::translate("Task", "\350\256\241\345\210\222\345\220\215\347\247\260", nullptr));
        groupBox_type->setTitle(QCoreApplication::translate("Task", "\344\272\213\344\273\266\347\261\273\345\236\213", nullptr));
        radioButton_Once->setText(QCoreApplication::translate("Task", "\345\215\225\346\254\241", nullptr));
        radioButton_Repeat->setText(QCoreApplication::translate("Task", "\351\207\215\345\244\215\345\236\213", nullptr));
        radioButton_Deadline->setText(QCoreApplication::translate("Task", "\346\227\245\346\234\237\346\210\252\346\255\242\345\236\213", nullptr));
        groupBox_priority->setTitle(QCoreApplication::translate("Task", "\344\272\213\344\273\266\344\274\230\345\205\210\347\272\247", nullptr));
        radioButton_high->setText(QCoreApplication::translate("Task", "\351\253\230", nullptr));
        radioButton_medium->setText(QCoreApplication::translate("Task", "\344\270\255", nullptr));
        radioButton_low->setText(QCoreApplication::translate("Task", "\344\275\216", nullptr));
        label_start->setText(QCoreApplication::translate("Task", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_end->setText(QCoreApplication::translate("Task", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        dateTimeEdit_end_once->setDisplayFormat(QCoreApplication::translate("Task", "yyyy/MM/dd HH:mm", nullptr));
        label_startDate->setText(QCoreApplication::translate("Task", "\345\274\200\345\247\213\346\227\245\346\234\237", nullptr));
        label_endDate->setText(QCoreApplication::translate("Task", "\347\273\223\346\235\237\346\227\245\346\234\237", nullptr));
        label_start_5->setText(QCoreApplication::translate("Task", "\347\232\204", nullptr));
        label_start_6->setText(QCoreApplication::translate("Task", "\345\210\260", nullptr));
        groupBox->setTitle(QString());
        checkBox_everyDay->setText(QCoreApplication::translate("Task", "\346\257\217\345\244\251", nullptr));
        checkBox_Monday->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\344\270\200", nullptr));
        checkBox_TuesDay->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\344\272\214", nullptr));
        checkBox_Wednesday->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\344\270\211", nullptr));
        checkBox_Thursday->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\345\233\233", nullptr));
        checkBox_Friday->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\344\272\224", nullptr));
        checkBox_Saturday->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\345\205\255", nullptr));
        checkBox_Sunday->setText(QCoreApplication::translate("Task", "\346\257\217\345\221\250\346\227\245", nullptr));
        label_end_deadline->setText(QCoreApplication::translate("Task", "\346\210\252\346\255\242\346\227\266\351\227\264", nullptr));
        pushButton_accept->setText(QCoreApplication::translate("Task", "\347\241\256\345\256\232", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("Task", "\345\217\226\346\266\210", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Task: public Ui_Task {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_H
