#include "chartwidget.h"
#include <QVBoxLayout>
#include <QDebug>

#include "chartwidget.h"

TasksBarChart::TasksBarChart(MyDataBase &db, const QDateTime &startTime, const QDateTime &endTime, const QString &title, QWidget *parent)
    : QWidget(parent), m_db(db), m_startTime(startTime), m_endTime(endTime), m_title(title)
{
    setupChart();
    setupAxis();
    loadData();
    adjustYAxisRange(); // 调整Y轴范围
}



void TasksBarChart::setupChart()
{
    m_chart = new QChart();
    m_series = new QBarSeries();
    m_chart->addSeries(m_series);
    m_chart->setTitle(m_title);
    m_chart->setTheme(QChart::ChartThemeLight);
    m_chart->legend()->setVisible(true);

    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    setLayout(layout);

    // 设置界面大小
    setMinimumSize(400, 300);
}

void TasksBarChart::setupAxis()
{
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("时长（小时）");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
}

void TasksBarChart::loadData()
{
    QList<StatisticData> data = m_db.findStatisticDataBetween(m_startTime, m_endTime);
    QList<StatisticData> classifiedData = m_db.classifyAndCalculateTotalTime(data);

    // 计算总时长
    int totalTime = 0;
    for (const StatisticData &stat : classifiedData) {
        totalTime += stat.count();
    }

    QStringList categories;
    QList<qreal> values;

    for (const StatisticData &stat : classifiedData) {
        categories << stat.name();
        values << stat.count();
    }

    QBarSet *set = new QBarSet("任务时长");
    for (const qreal &value : values) {
        *set << value;
        qDebug() << "value" << value;
    }

    // 设置柱状图颜色
    set->setColor(Qt::blue);

    m_series->append(set);

    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis*>(m_chart->axes(Qt::Horizontal).at(0));
    if (axisX) {
        axisX->append(categories);
        qDebug() << "Categories set on axisX: " << categories;
    }
    for (QGraphicsItem *item : m_chart->scene()->items()) {
        if (qgraphicsitem_cast<QGraphicsSimpleTextItem *>(item)) {
            m_chart->scene()->removeItem(item);
            delete item;
        }
    }
    // 显示具体值和百分比
    for (int i = 0; i < set->count(); ++i) {
        QBarSet *barSet = m_series->barSets().at(0);
        qreal value = barSet->at(i);
        qreal percentage = (value / totalTime) * 100.0;

        QString labelText = QString::number(value) + "小时 (" + QString::number(percentage, 'f', 2) + "%)";
        QGraphicsSimpleTextItem *label = new QGraphicsSimpleTextItem(labelText);

        qreal xPos = m_chart->plotArea().left() + (i + 0.5) * (m_chart->plotArea().width() / set->count()) - 10;
        qreal yPos = m_chart->plotArea().bottom() - (value / ((QValueAxis*)m_chart->axes(Qt::Vertical).at(0))->max()) * m_chart->plotArea().height() - 20;

        label->setPos(xPos, yPos);
        m_chart->scene()->addItem(label);
    }
    // update();
}


void TasksBarChart::adjustYAxisRange()
{
    QValueAxis *axisY = qobject_cast<QValueAxis*>(m_chart->axes(Qt::Vertical).at(0));
    if (!axisY)
        return;

    // 计算Y轴的最大值
    qreal maxValue = 0;
    for (const QBarSet *set : m_series->barSets()) {
        for (int i = 0; i < set->count(); ++i) {
            if (set->at(i) > maxValue)
                maxValue = set->at(i);
        }
    }

    // 设置Y轴的范围
    axisY->setRange(0, maxValue +1); // 增加一些空间以便显示标签
}

void TasksBarChart::updateData(const QDateTime &startTime, const QDateTime &endTime)
{
    MyDataBase db;db.openDb();
    m_startTime=startTime;
    m_endTime=endTime;
    m_series->clear();


    QList<QAbstractAxis*> axes = m_chart->axes();
    for (QAbstractAxis* axis : axes) {
        m_chart->removeAxis(axis);
        delete axis;
    }
    setupAxis();
    loadData();
    adjustYAxisRange();
}



// TasksPieChart 实现
TasksPieChart::TasksPieChart(MyDataBase &db, const QDateTime &startTime, const QDateTime &endTime, const QString &title, QWidget *parent)
    : QWidget(parent), m_db(db), m_startTime(startTime), m_endTime(endTime)
{
    setupChart(title);
    loadData();
}

void TasksPieChart::updateData(const QDateTime &startTime, const QDateTime &endTime)
{
    MyDataBase db;db.openDb();
    m_startTime=startTime;
    m_endTime=endTime;
    m_series->clear();
    loadData();
}

void TasksPieChart::setupChart(const QString &title)
{
    m_chart = new QChart();
    m_series = new QPieSeries();
    m_chart->addSeries(m_series);
    m_chart->setTitle(title);
    m_chart->setTheme(QChart::ChartThemeLight);
    m_chart->legend()->setVisible(true);

    QChartView *chartView = new QChartView(m_chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    setLayout(layout);

    // 设置界面大小
    setMinimumSize(400, 300);
}

void TasksPieChart::loadData()
{
    QList<StatisticData> data = m_db.findStatisticDataBetween(m_startTime, m_endTime);
    QList<StatisticData> classifiedData = m_db.classifyAndCalculateTotalTime(data);

    // 计算总时长
    int totalTime = 0;
    for (const StatisticData &stat : classifiedData) {
        totalTime += stat.count();
    }

    for (const StatisticData &stat : classifiedData) {
        qreal percentage = (stat.count() / (qreal)totalTime) * 100.0;
        QPieSlice *slice = m_series->append(stat.name() + QString(" (%1h, %2%)").arg(stat.count()).arg(percentage, 0, 'f', 2), stat.count());
        slice->setLabelVisible();
        slice->setLabelFont(QFont("Arial", 8));
    }
}


DateRangeChartWidget::DateRangeChartWidget(MyDataBase &db, QWidget *parent)
    : QWidget(parent)
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime startOfToday = now.date().startOfDay();
    QDateTime endOfToday = now.date().endOfDay();
    m_barChart = new TasksBarChart(db,startOfToday,endOfToday,"代办统计",this);
    m_pieChart = new TasksPieChart(db,startOfToday,endOfToday,"代办统计",this);

    m_dateEditStart = new QDateTimeEdit(this);
    m_dateEditStart->setDisplayFormat("yyyy-MM-dd");
    m_dateEditEnd = new QDateTimeEdit(this);
    m_dateEditEnd->setDisplayFormat("yyyy-MM-dd");
    m_dateEditStart->setCalendarPopup(true);
    m_dateEditEnd->setCalendarPopup(true);
    m_dateEditStart->setMinimumWidth(100);
    m_dateEditEnd->setMinimumWidth(100);

    acceptButton = new QPushButton("确认",this);
    QLabel* l1=new QLabel("起始日期",this);
    QLabel* l2=new QLabel("终止日期",this);
    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    QHBoxLayout *buttonlayout = new QHBoxLayout(this);
    QHBoxLayout *chartslayout = new QHBoxLayout(this);
    buttonlayout->addStretch();
    buttonlayout->addWidget(l1);
    buttonlayout->addWidget(m_dateEditStart);
    buttonlayout->addStretch();
    buttonlayout->addWidget(l2);
    buttonlayout->addWidget(m_dateEditEnd);
    buttonlayout->addStretch();
    buttonlayout->addWidget(acceptButton);
    buttonlayout->addStretch();
    chartslayout->addWidget(m_barChart);
    chartslayout->addWidget(m_pieChart);
    mainlayout->addLayout(buttonlayout);
    mainlayout->addLayout(chartslayout);
    setLayout(mainlayout);
    connect(acceptButton, &QPushButton::clicked, this, &DateRangeChartWidget::updateCharts);

    // 默认使用当前日期范围
    setDateRange(QDateTime::currentDateTime().date().startOfDay(), QDateTime::currentDateTime().date().endOfDay());
}

void DateRangeChartWidget::setDateRange(const QDateTime &start, const QDateTime &end)
{
    m_dateEditStart->setDateTime(start);
    m_dateEditEnd->setDateTime(end);
    updateCharts();
}

void DateRangeChartWidget::updateCharts()
{
    QDateTime start = m_dateEditStart->dateTime();
    QDateTime end = m_dateEditEnd->dateTime();
    if(end<start){
        QMessageBox::warning(this, "错误", "任务的开始时间必须早于结束时间！");
        return;
    }
    m_barChart->updateData(start, end);
    m_pieChart->updateData(start, end);
}
