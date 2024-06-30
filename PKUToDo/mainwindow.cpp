#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "STCalendarWidget.h"
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
    calendar = new STCalendarWidget(this);
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
// 设置待办页
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabWidgetCurrentChanged);
    QWidget* tab_todo = ui->tab_toDo;
    QHBoxLayout* tabLayout_todo = new QHBoxLayout(tab_todo);
    TodayTasksWidget* todayWidget = new TodayTasksWidget(this);
    ToDoView* toDoView = new ToDoView(this);
    MyDataBase db;
    db.openDb();
    toDoView->setDatabase(&db);
    tabLayout_todo->addWidget(todayWidget);
    tabLayout_todo->addWidget(toDoView);
    tab_todo->setLayout(tabLayout_todo);
//设置页
    QWidget* tab_setting = ui->tab_settings;
    QGroupBox* groupBox = new QGroupBox("主题设置", tab_setting);

    QRadioButton* noneRadioButton = new QRadioButton("无", groupBox);
    QRadioButton* blueRadioButton = new QRadioButton("蓝色", groupBox);
    QRadioButton* blackRadioButton = new QRadioButton("黑色", groupBox);


    QHBoxLayout *layout = new QHBoxLayout(groupBox);
    layout->addWidget(noneRadioButton);
    layout->addWidget(blueRadioButton);
    layout->addWidget(blackRadioButton);


    groupBox->setLayout(layout);
    groupBox->setGeometry(20, 20, 200, 150);

    noneRadioButton->setChecked(true);
    onThemeChanged("noneStyle.qss");
    // 连接槽函数
    connect(noneRadioButton, &QRadioButton::clicked, this, [=](){ onThemeChanged("noneStyle.qss"); });
    connect(blueRadioButton, &QRadioButton::clicked, this, [=](){ onThemeChanged("blueStyle.qss"); });
    connect(blackRadioButton, &QRadioButton::clicked, this, [=](){ onThemeChanged("blackStyle.qss"); });

    //统计页
    // QDateTime now = QDateTime::currentDateTime();
    // QDateTime startOfToday = now.date().startOfDay();
    // QDateTime endOfToday = now.date().endOfDay();

    // QWidget* tab_statistic = ui->tab_statistics;
    // QHBoxLayout *mainLayout = new QHBoxLayout(tab_statistic);
    // TasksBarChart *barChart = new TasksBarChart(db, startOfToday, endOfToday, "今日任务完成情况");
    // TasksPieChart *pieChart = new TasksPieChart(db, startOfToday, endOfToday, "今日任务时间分布");
    // mainLayout->addWidget(barChart);
    // mainLayout->addWidget(pieChart);
    QWidget* tab_statistic = ui->tab_statistics;
    QHBoxLayout *mainLayout = new QHBoxLayout(tab_statistic);
    DateRangeChartWidget* charts=new DateRangeChartWidget(db,this);
    mainLayout->addWidget(charts);
    //主页设置


    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::loadTheme(const QString& themeName) {
    if (!themeName.isEmpty()) {
        if(themeName=="blackStyle.qss"){
            calendar->setTheme("black");
            for (int i = 0; i < 42; i++) {
                calendar->datewidgets[i]->setTheme("black");
                calendar->datewidgets[i]->update();
            }
            calendar->update();
        }
        else{
            calendar->setTheme("blue");
            for (int i = 0; i < 42; i++) {
                calendar->datewidgets[i]->setTheme("blue");
                calendar->datewidgets[i]->update();
            }
            calendar->update();
        }
        QFile file(":/styles/styles/"+themeName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream stream(&file);
            qApp->setStyleSheet(stream.readAll());
            file.close();
            currentTheme = themeName;
        }
    }
}

void MainWindow::onThemeChanged(const QString& themeName) {
    loadTheme(themeName);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HaveDateChose(QDate selectedDate)
{
    TimeAxisWindow *timeAxisWindow = new TimeAxisWindow(selectedDate);
    if(currentTheme=="blackStyle.qss"){
        timeAxisWindow->setTheme("black");
        timeAxisWindow->timeAxis->resetScene();

    }
    timeAxisWindow->show();
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/widgets_icons/wristwatch.png"), QSize(), QIcon::Normal, QIcon::Off);
    timeAxisWindow->setWindowIcon(icon);
}

void MainWindow::onTabWidgetCurrentChanged(int index)
{

}


void MainWindow::on_pushButton_intro_clicked()
{
    QString websiteUrl = "https://github.com/AibohDij/Qt_Time_Schedule"; // 替换为您要打开的网址
    QDesktopServices::openUrl(QUrl(websiteUrl));
}

