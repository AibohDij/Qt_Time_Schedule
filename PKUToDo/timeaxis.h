#ifndef TIMEAXIS_H
#define TIMEAXIS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QDebug>
#include<QList>
#include <QMainWindow>
#include "taskwidget.h"
#include "taskdata.h"
#include "task.h"
#include "mydatabase.h"
#include <QMenu>
#include <QAction>

class TimeAxis : public QGraphicsView {
    Q_OBJECT

public:
    TimeAxis(int windowWidth, int windowHeight, qreal stride, QDate date=QDate::currentDate(), QWidget *parent = nullptr);
    QString theme="none";
    void resetScene();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
public slots:
    void updateTimeAxis(TaskWidget* widget);
    void drawDayTasks();
    //void deleteTaskWidget(TaskWidget *widget);
    void addnewTask();
private:
    void setupTimeAxis();
    TaskWidget * addTaskWidget(const TaskData &taskData);


    QGraphicsScene *scene;
    QGraphicsTextItem *dateTextItem;
    int windowWidth;
    int windowHeight;
    qreal stride;
    QDate today;
};




class TimeAxisWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimeAxisWindow(QDate selectedDate, QWidget *parent = nullptr);
    QString theme="none";
    void setTheme(QString t);
    TimeAxis *timeAxis;
private:

};


class WeeklyTimeAxis : public QGraphicsView {
    Q_OBJECT

public:
    explicit WeeklyTimeAxis(int windowWidth, int windowHeight, qreal stride, QDate startDate, QWidget *parent = nullptr);

public slots:
    void drawWeekTasks(); // 绘制一周的任务

private:
    QGraphicsScene *scene;
    int windowWidth;
    int windowHeight;
    qreal stride;
    QDate startDate;
    QDate endDate;

    void setupWeekAxis(); // 设置一周的时间轴
    void addTaskWidget(const TaskData &taskData); // 添加任务小部件
    void updateWeekDates(); // 更新一周的日期范围
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

class WeeklyTimeAxisWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit WeeklyTimeAxisWindow(QDate selectedDate, QWidget *parent = nullptr);

    //void setTheme(QString t);

private:
    WeeklyTimeAxis *weeklyTimeAxis;
    QString theme = "none";

};


#endif // TIMEAXIS_H
