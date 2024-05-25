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
#include <QComboBox>
#include <QLineEdit>


#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFormLayout>

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


class ToDoEditDialog : public QDialog {
    Q_OBJECT

public:
    explicit ToDoEditDialog(QWidget *parent = nullptr);
    ~ToDoEditDialog();
    ToDoData generateToDo();
    void setToDoData(const ToDoData &data);
    void setDatabase(MyDataBase *db);

private slots:
    void on_buttonBox_accepted();

private:
    QLineEdit *nameLineEdit;
    QSpinBox *hoursSpinBox;
    QSpinBox *minutesSpinBox;
    QComboBox *priorityComboBox;
    QCheckBox *isDoneCheckBox;
    QDialogButtonBox *buttonBox;

    MyDataBase *m_db;
    ToDoData m_toDoData;
    bool m_isEditMode;
signals:
    void editFinished();
};


#endif // TASK_H
