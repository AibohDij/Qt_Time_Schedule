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
//设置日历页
    QWidget* tab_Calendar=ui->tab_calendar;
    QHBoxLayout *tabLayout_Calendar = new QHBoxLayout(tab_Calendar);
    calendar = new STCalandarWidget(this);
        // 连接信号槽
    connect(calendar, SIGNAL(DateSelectSignal(QDate)), this, SLOT(HaveDateChose(QDate)));
    tabLayout_Calendar->addStretch();
    tabLayout_Calendar->addWidget(calendar);
    tabLayout_Calendar->addStretch();
    tab_Calendar->setLayout(tabLayout_Calendar);

//设置搜索页
    QWidget* tab_search = ui->tab_search;
    QHBoxLayout* tabLayout_search = new QHBoxLayout(tab_search); // 创建水平布局
    SearchWidget* searchWidget = new SearchWidget(this); // 创建 SearchWidget 实例
    tabLayout_search->addWidget(searchWidget);
    tabLayout_search->setAlignment(Qt::AlignTop); // 设置布局顶部对齐
    tab_search->setLayout(tabLayout_search); // 将布局设置到 tab_search 页面中
// 设置代办页
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabWidgetCurrentChanged);
    QWidget* tab_todo = ui->tab_toDo;
    QHBoxLayout* tabLayout_todo = new QHBoxLayout(tab_todo);
    TodayTasksWidget* todayWidget = new TodayTasksWidget(this);
    ToDoView* toDoView = new ToDoView(this);
    MyDataBase db;db.openDb();
    toDoView->setDatabase(&db);
    tabLayout_todo->addWidget(todayWidget);
    tabLayout_todo->addWidget(toDoView);
    tab_todo->setLayout(tabLayout_todo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HaveDateChose(QDate selectedDate)
{
    TimeAxisWindow *timeAxisWindow = new TimeAxisWindow(selectedDate);
    timeAxisWindow->show();
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/widgets_icons/wristwatch.png"), QSize(), QIcon::Normal, QIcon::Off);
    timeAxisWindow->setWindowIcon(icon);
}

void MainWindow::onTabWidgetCurrentChanged(int index)
{

}
