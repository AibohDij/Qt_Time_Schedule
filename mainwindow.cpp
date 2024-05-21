#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "STCalandarWidget.h"
#include "STDateWidget.h"
#include <qboxlayout.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* tab_Calendar=ui->tab_calendar;
    QHBoxLayout *tabLayout_Calendar = new QHBoxLayout(tab_Calendar);
    calendar = new STCalandarWidget(this);
    // 连接信号槽
    connect(calendar, SIGNAL(DateSelectSignal(QDate)), this, SLOT(HaveDateChose(QDate)));
    tabLayout_Calendar->addWidget(calendar);
    tabLayout_Calendar->addStretch();
    tab_Calendar->setLayout(tabLayout_Calendar);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HaveDateChose(QDate selectedDate)
{
    TimeAxisWindow *timeAxisWindow = new TimeAxisWindow(selectedDate);
    timeAxisWindow->show();
}

