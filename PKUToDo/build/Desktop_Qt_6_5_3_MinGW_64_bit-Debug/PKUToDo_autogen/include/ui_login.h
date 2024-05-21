/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout;
    QLabel *emailLabel;
    QLineEdit *emailEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *submit;
    QPushButton *cancel;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(375, 303);
        label = new QLabel(login);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 70, 251, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(15);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        layoutWidget_2 = new QWidget(login);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(80, 120, 201, 61));
        formLayout = new QFormLayout(layoutWidget_2);
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setContentsMargins(0, 0, 0, 0);
        emailLabel = new QLabel(layoutWidget_2);
        emailLabel->setObjectName("emailLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, emailLabel);

        emailEdit = new QLineEdit(layoutWidget_2);
        emailEdit->setObjectName("emailEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, emailEdit);

        passwordLabel = new QLabel(layoutWidget_2);
        passwordLabel->setObjectName("passwordLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordEdit = new QLineEdit(layoutWidget_2);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordEdit);

        widget = new QWidget(login);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(90, 220, 191, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        submit = new QPushButton(widget);
        submit->setObjectName("submit");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(submit->sizePolicy().hasHeightForWidth());
        submit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(submit);

        cancel = new QPushButton(widget);
        cancel->setObjectName("cancel");
        sizePolicy.setHeightForWidth(cancel->sizePolicy().hasHeightForWidth());
        cancel->setSizePolicy(sizePolicy);
        cancel->setAutoRepeat(false);
        cancel->setFlat(false);

        horizontalLayout->addWidget(cancel);


        retranslateUi(login);

        cancel->setDefault(false);


        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("login", "<html><head/><body><p>\347\231\273\345\275\225</p></body></html>", nullptr));
        emailLabel->setText(QCoreApplication::translate("login", "\350\264\246\345\217\267", nullptr));
        passwordLabel->setText(QCoreApplication::translate("login", "\345\257\206\347\240\201", nullptr));
        submit->setText(QCoreApplication::translate("login", "Submit", nullptr));
        cancel->setText(QCoreApplication::translate("login", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
