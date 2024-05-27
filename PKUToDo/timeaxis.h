#ifndef TIMEAXIS_H
#define TIMEAXIS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QMainWindow>
#include "taskwidget.h"
#include "taskdata.h"
#include "task.h"
#include "mydatabase.h"

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


#endif // TIMEAXIS_H
