#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "taskdata.h"

class TaskWidget : public QWidget {
    Q_OBJECT

public:
    TaskWidget(const TaskData &taskData, qreal height,QDate today = QDate::currentDate(), QWidget *parent = nullptr);
    void contextMenuEvent(QContextMenuEvent *event) override;
    TaskData m_taskData;
signals:
    void editFinished(TaskWidget* widget);


private:

    QDate m_today;
    void setupUi(const TaskData &taskData);
    QString getPriorityColor(Priority priority);
    void adjustFontSizeToFit(QLabel *timeLabel, QLabel *nameLabel);

private slots:
    void onEditTask();
    void onDeleteTask();
};

#endif // TASKWIDGET_H
