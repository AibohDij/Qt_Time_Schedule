#ifndef STCALANDARWIDGET_H
#define STCALANDARWIDGET_H

#endif // STCALANDARWIDGET_H
#pragma once
#include <qdialog.h>
#include "STDateWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
class STCalandarWidget :
                         public QDialog
{
    Q_OBJECT
public:
    STCalandarWidget(QWidget* parrent = nullptr);
    ~STCalandarWidget();
    void SetCurrentDate(int year, int month, int day);
    QDate GetCurrentDate();
    void setTheme(QString s);
    QString theme="blue";

    STDateWidget *datewidgets[42];
private:
    void FillCalandar();
    void initLabels();
    void initCalandar();
    void init();
    QString getFormatMonth();
private:
    QLabel *weeklabels[7];

    QPushButton *lastYearButton;
    QPushButton *lastMonthButton;
    QPushButton *nextMonthButton;
    QPushButton *nextYearButton;
    QDate currentDate;
    QLabel *cdlabel;
    //My Revise
    QLineEdit *yearLineEdit;
    QSpinBox *monthSpinBox;
    QPushButton *setYearMonth;

public slots:
    void HaveDateSelect(QDate date);
    void JumpLastYear();
    void JumpLastMonth();
    void JumpNextMonth();
    void JumpNextYear();
    void SetDate();
signals:
    void DateSelectSignal(QDate date);
};
