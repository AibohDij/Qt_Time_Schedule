// searchwidget.h
#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <algorithm>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMessageBox>
#include "mydatabase.h"
#include "taskdata.h"
#include "task.h"
#include "flipclockwidget.h"

class SearchWidget : public QWidget {
    Q_OBJECT

public:
    SearchWidget(QWidget *parent = nullptr);

private slots:
    void onSearchButtonClicked();
    void onNewTaskButtonClicked();

private:
    QLineEdit *taskNameEdit;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QComboBox *priorityComboBox;
    QPushButton *searchButton;
    QPushButton *newTaskButton;
    QTableWidget *resultsTable;

    void setupUi();
    void displayResults(const QList<TaskData> &tasks);


};


class TodayTasksWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TodayTasksWidget(QWidget *parent = nullptr);

private slots:
    void TodayUpdate();
    void newTask();

private:
    QTableWidget *tasksTable;

    void setupUi();
    void displayTodayTasks();

signals:

};



// 定义新的SearchResultWidget类

class SearchResultWidget : public QWidget {
    Q_OBJECT

public:
    SearchResultWidget(const TaskData &taskData, QWidget *parent = nullptr);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    TaskData m_taskData;

    void setupUi();
    QString getPriorityColor(Priority priority);
    QString priorityToString(Priority priority);
public slots:
    void onEdit();
    void onDelete();

signals:
    void editFinished();

};

class ToDoWidget : public QWidget {
    Q_OBJECT

public:
    explicit ToDoWidget(const ToDoData &toDoData, QWidget *parent = nullptr);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    QLabel *nameLabel;
    QLabel *expectTimeLabel;
    bool isDone = false;
    ToDoData m_data;
    QPushButton *startButton;
    void setPriorityColor(Priority priority);
public slots:
    void on_startButton_clicked();
    void onEdit();
    void onDelete();
    void onRenew();
    void setComplete();
signals:
    void editFinished();
};

class ToDoView : public QWidget {
    Q_OBJECT

public:
    explicit ToDoView(QWidget *parent = nullptr);
    void setDatabase(MyDataBase *db);

private slots:
    void onAddButtonClicked();
    void refreshToDoList();

private:
    MyDataBase *m_db;
    QPushButton *addButton;
    QTableWidget *tableWidget;

    void populateTable();
};


#endif // SEARCHWIDGET_H
