#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

#include "taskdata.h"

class MyDataBase
{
public:
    //构造函数
    MyDataBase();
    // 打开数据库
    bool openDb(void);
    // 创建数据表
    void createTable(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    // 关闭数据库
    void closeDb(void);
    void clearTable(const QString &tableName);
    void dropTable(const QString &tableName);
    void resetAutoIncrement(const QString &tableName);
    //插入TaskData类型数据
    void insertTaskData(const TaskData &taskData);
    void deleteTaskData(int taskId);
    void deleteTaskData(const TaskData &taskData);
    void modifyTaskData(const TaskData &taskData, int taskId);
    void modifyTaskData(const TaskData &taskData, const TaskData &newTaskData);
    //查找函数群
    void queryTaskData();
    QList<TaskData> findTaskData(const QString &condition);
    QList<TaskData> findTaskData(const QString &taskName, const QDate &startDate, const QDate &endDate, Priority priority);
    QList<TaskData> findTaskDataByDate(const QDate &date);
    //去重
    void removeDuplicateTasks();
    //Todo类相关函数定义
    // 插入ToDoData
    void insertToDoData(const ToDoData &toDoData);
    void deleteToDoData(const ToDoData &toDoData);
    void modifyToDoData(const ToDoData &toDoData, const ToDoData &newToDoData);
    void queryToDoData();
    QList<ToDoData> findToDoData(const QString &condition);
    void deleteToDoData(int toDoId);
    void modifyToDoData(const ToDoData &toDoData, int toDoId);
    void removeDuplicateToDoData();

private:
    QSqlDatabase database;
};

#endif // MYDATABASE_H
