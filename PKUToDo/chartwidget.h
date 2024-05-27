#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDateTimeEdit>
#include "mydatabase.h"





class TasksBarChart : public QWidget
{
    Q_OBJECT

public:
    explicit TasksBarChart(MyDataBase &db, const QDateTime &startTime, const QDateTime &endTime, const QString &title, QWidget *parent = nullptr);
    void updateData(const QDateTime &startTime, const QDateTime &endTime);
private:
    void setupChart();
    void setupAxis();
    void loadData();
    void adjustYAxisRange();


    MyDataBase &m_db;
    QChart *m_chart;
    QBarSeries *m_series;
    QDateTime m_startTime;
    QDateTime m_endTime;
    QString m_title;
    int m_totalTime=1;
    int m_maxValue=1;
};

class TasksPieChart : public QWidget
{
    Q_OBJECT

public:
    explicit TasksPieChart(MyDataBase &db, const QDateTime &startTime, const QDateTime &endTime, const QString &title, QWidget *parent = nullptr);
    void updateData(const QDateTime &startTime, const QDateTime &endTime);
private:
    void setupChart(const QString &title);
    void loadData();

    MyDataBase &m_db;
    QChart *m_chart;
    QPieSeries *m_series;
    QDateTime m_startTime;
    QDateTime m_endTime;
};



class DateRangeChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateRangeChartWidget(MyDataBase &db, QWidget *parent = nullptr);
    void setDateRange(const QDateTime &start, const QDateTime &end);

private:
    QPushButton *acceptButton;
    TasksBarChart *m_barChart;
    TasksPieChart *m_pieChart;
    QDateTimeEdit *m_dateEditStart;
    QDateTimeEdit *m_dateEditEnd;

private slots:
    void updateCharts();
};

#endif // CHARTWIDGET_H
