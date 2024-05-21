#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDate>
#include<QStackedWidget>
#include <QMessageBox>

#include "taskdata.h"
#include "mydatabase.h"
#include "taskwidget.h"

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QWidget *parent = nullptr);
    ~Task();
    //从TaskData类设置widget
    void setTaskData(const TaskData &data);
    void setModifyMode(const TaskData &originTask);
    //生成TaskData
    TaskData getData();
    TaskData generatetask();
private slots:
    void on_pushButton_accept_clicked();

    void on_pushButton_cancel_clicked();


    void TimeSetting();
private:
    Ui::Task *ui;
    QDateTimeEdit * StartTimeEdit;
    QDateTimeEdit * EndTimeEdit;
    TaskType type = SingleTask;
    bool isModifyMode=false;
    TaskData originData;
};

#endif // TASK_H
