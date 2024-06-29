#include "mainwindow.h"

#include "task.h"
#include "timeaxis.h"
#include "taskdata.h"
#include "mydatabase.h"
#include "searchwidget.h"
#include "chartwidget.h"
#include "flipclockwidget.h"
#include <QApplication>

void demo();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();

    //测试代码 实际可删
    demo();
    return a.exec();
}

void demo(){
    MyDataBase db;
    if (!db.openDb())
    {
        return;
    }
    db.createTable();
    db.clearTable("task_data_table");
    db.clearTable("todo_data_table");
    db.clearTable("statistic_table");
    QDateTime now = QDateTime::currentDateTime();
    QDateTime startOfToday = now.date().startOfDay();
    //QDateTime endOfToday = now.date().endOfDay();
    QList<StatisticData> sampleData = {
        {"任务 A", startOfToday.addDays(-1).addSecs(3600), startOfToday.addDays(-1).addSecs(9200)}, // 1小时到2小时
        {"任务 B", startOfToday.addSecs(5400), startOfToday.addSecs(10800)}, // 2小时到3小时
        {"任务 C", startOfToday.addSecs(10800), startOfToday.addSecs(17800)}, // 3小时到4小时
        {"任务 D", startOfToday.addSecs(14400), startOfToday.addSecs(36000)}, // 4小时到5小时
    };

    for (const StatisticData &data : sampleData) {
        db.insertStatisticData(data);
    }

    //db.clearTable("task_data_table");
    TaskData task1(QDateTime(QDate::currentDate(), QTime(8, 0)), QDateTime(QDate::currentDate(), QTime(9, 0)), "Single Task 1", "Single Task 1 details", HighPriority, SingleTask, false, false);
    // RepeatedTask for today
    std::array<bool, 7> repeatDays = {false, true, false, false, false, false, false}; // Repeat on Tuesday
    TaskData task2(QDateTime(QDate::currentDate(), QTime(10, 0)), QDateTime(QDate::currentDate(), QTime(11, 0)), "Repeated Task 1", "Repeated Task 1 details", MediumPriority, RepeatedTask, false, false, repeatDays);

    std::array<bool, 7> RepeatDays = {true, true, false, false, false, false, false}; // Repeat on Tuesday
    TaskData task7(QDateTime(QDate::currentDate(), QTime(10, 0)), QDateTime(QDate::currentDate(), QTime(11, 0)), "Repeated Task 2", "Repeated Task 1 details", MediumPriority, RepeatedTask, false, false, RepeatDays);
    // DeadlineTask for today
    TaskData task3(QDateTime(QDate::currentDate(), QTime(12, 0)), QDateTime(QDate::currentDate(), QTime(19, 0)), "Deadline Task 1", "Deadline Task 1 details", LowPriority, DeadlineTask, false, false);

    // Insert tasks into the database
    db.insertTaskData(task1);
    db.insertTaskData(task2);
    db.insertTaskData(task3);
    db.insertTaskData(task7);

    // SingleTask for tomorrow
    TaskData task4(QDateTime(QDate::currentDate().addDays(1), QTime(8, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(9, 0)), "Single Task 2", "Single Task 2 details", HighPriority, SingleTask, false, false);

    // RepeatedTask for tomorrow
    std::array<bool, 7> repeatDaysTomorrow = {false, false, true, false, false, false, false}; // Repeat on Wednesday
    TaskData task5(QDateTime(QDate::currentDate().addDays(1), QTime(10, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(11, 0)), "Repeated Task 2", "Repeated Task 2 details", MediumPriority, RepeatedTask, false, false, repeatDaysTomorrow);

    // DeadlineTask for tomorrow
    TaskData task6(QDateTime(QDate::currentDate().addDays(1), QTime(12, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(15, 0)), "Deadline Task 2", "Deadline Task 2 details", LowPriority, DeadlineTask, false, false);

    // Insert tasks into the database
    db.insertTaskData(task4);
    db.insertTaskData(task5);
    db.insertTaskData(task6);
    db.removeDuplicateTasks();
    db.queryTaskData();

    QList<ToDoData> sampleToDoData={
        {"背单词",600,LowPriority},
        {"程设视频录制",7200,HighPriority},
        {"高数作业",5400,MediumPriority }
    };
    for (const ToDoData &data : sampleToDoData) {
        db.insertToDoData(data);
    }
    db.removeDuplicateToDoData();


    db.closeDb();
}

//图表测试代码
// db.clearTable("statistic_table");
// QDateTime now = QDateTime::currentDateTime();
// QDateTime startOfToday = now.date().startOfDay();
// QDateTime endOfToday = now.date().endOfDay();

// QList<StatisticData> sampleData = {
//     {"任务 A", startOfToday.addSecs(3600), startOfToday.addSecs(9200)}, // 1小时到2小时
//     {"任务 B", startOfToday.addSecs(5400), startOfToday.addSecs(10800)}, // 2小时到3小时
//     {"任务 C", startOfToday.addSecs(10800), startOfToday.addSecs(17800)}, // 3小时到4小时
//     {"任务 D", startOfToday.addSecs(14400), startOfToday.addSecs(36000)}, // 4小时到5小时
// };

// for (const StatisticData &data : sampleData) {
//     db.insertStatisticData(data);
// }

// QWidget mainWidget;
// QHBoxLayout *mainLayout = new QHBoxLayout(&mainWidget);

// TasksBarChart *barChart = new TasksBarChart(db, startOfToday, endOfToday, "今日任务完成情况");
// TasksPieChart *pieChart = new TasksPieChart(db, startOfToday, endOfToday, "今日任务时间分布");

// mainLayout->addWidget(barChart);
// mainLayout->addWidget(pieChart);

// mainWidget.show();



// QDateTime startTime1 = QDateTime::fromString("2024-05-01T10:00:00", Qt::ISODate);
// QDateTime endTime1 = QDateTime::fromString("2024-05-01T12:00:00", Qt::ISODate);
// StatisticData data1("Task A", startTime1, endTime1);
// db.insertStatisticData(data1);

// QDateTime startTime2 = QDateTime::fromString("2024-05-02T13:00:00", Qt::ISODate);
// QDateTime endTime2 = QDateTime::fromString("2024-05-02T14:00:00", Qt::ISODate);
// StatisticData data2("Task B", startTime2, endTime2);
// db.insertStatisticData(data2);

// QDateTime startTime3 = QDateTime::fromString("2024-05-03T09:00:00", Qt::ISODate);
// QDateTime endTime3 = QDateTime::fromString("2024-05-03T13:00:00", Qt::ISODate);
// StatisticData data3("Task C", startTime3, endTime3);
// db.insertStatisticData(data3);

// QDateTime startTime4 = QDateTime::fromString("2024-05-04T11:00:00", Qt::ISODate);
// QDateTime endTime4 = QDateTime::fromString("2024-05-04T19:00:00", Qt::ISODate);
// StatisticData data4("Task D", startTime4, endTime4);
// db.insertStatisticData(data4);
// db.queryStatisticData();
// //db.clearTable("statistic_table");
// QDateTime startTime = QDateTime::fromString("2024-05-01T00:00:00", Qt::ISODate);
// QDateTime endTime = QDateTime::fromString("2024-05-07T23:59:59", Qt::ISODate);

// QList<StatisticData> data = db.findStatisticDataBetween(startTime, endTime);

// BarChartWidget barChart;
// barChart.setData(data);
// barChart.resize(100, 100);
// barChart.show();

// PieChartWidget pieChart;
// pieChart.setData(data);
// pieChart.resize(200, 200);
// pieChart.show();

//创建/打开表

// 数据库 查找某个date数据测试代码

// // SingleTask for today
// TaskData task1(QDateTime(QDate::currentDate(), QTime(8, 0)), QDateTime(QDate::currentDate(), QTime(9, 0)), "Single Task 1", "Single Task 1 details", HighPriority, SingleTask, false, false);
// // RepeatedTask for today
// std::array<bool, 7> repeatDays = {false, true, false, false, false, false, false}; // Repeat on Tuesday
// TaskData task2(QDateTime(QDate::currentDate(), QTime(10, 0)), QDateTime(QDate::currentDate(), QTime(11, 0)), "Repeated Task 1", "Repeated Task 1 details", MediumPriority, RepeatedTask, false, false, repeatDays);

// std::array<bool, 7> RepeatDays = {true, true, false, false, false, false, false}; // Repeat on Tuesday
// TaskData task7(QDateTime(QDate::currentDate(), QTime(10, 0)), QDateTime(QDate::currentDate(), QTime(11, 0)), "Repeated Task 1", "Repeated Task 1 details", MediumPriority, RepeatedTask, false, false, RepeatDays);
// // DeadlineTask for today
// TaskData task3(QDateTime(QDate::currentDate(), QTime(12, 0)), QDateTime(QDate::currentDate(), QTime(13, 0)), "Deadline Task 1", "Deadline Task 1 details", LowPriority, DeadlineTask, false, false);

// // Insert tasks into the database
// db.insertTaskData(task1);
// db.insertTaskData(task2);
// db.insertTaskData(task3);
// db.insertTaskData(task7);

// // SingleTask for tomorrow
// TaskData task4(QDateTime(QDate::currentDate().addDays(1), QTime(8, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(9, 0)), "Single Task 2", "Single Task 2 details", HighPriority, SingleTask, false, false);

// // RepeatedTask for tomorrow
// std::array<bool, 7> repeatDaysTomorrow = {false, false, true, false, false, false, false}; // Repeat on Wednesday
// TaskData task5(QDateTime(QDate::currentDate().addDays(1), QTime(10, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(11, 0)), "Repeated Task 2", "Repeated Task 2 details", MediumPriority, RepeatedTask, false, false, repeatDaysTomorrow);

// // DeadlineTask for tomorrow
// TaskData task6(QDateTime(QDate::currentDate().addDays(1), QTime(12, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(13, 0)), "Deadline Task 2", "Deadline Task 2 details", LowPriority, DeadlineTask, false, false);

// // Insert tasks into the database
// db.insertTaskData(task4);
// db.insertTaskData(task5);
// db.insertTaskData(task6);
// db.queryTaskData();
// QVector<TaskData> tasks = db.findTaskDataByDate(QDate::currentDate());

// // 打印查询结果
// qDebug() << "Tasks found for TaskType 0 and date " << QDate::currentDate().toString("yyyy-MM-dd") << ":";

// for (const auto &task : tasks) {
//     qDebug() << "Task Name: " << task.name()
//              << ", Start Time: " << task.startTime().toString("yyyy-MM-dd HH:mm:ss");
// }



//Task TimeAxis 全功能测试
/*
    TaskData task1(QDateTime(QDate::currentDate(), QTime(8, 0)), QDateTime(QDate::currentDate(), QTime(9, 0)), "Single Task 1", "Single Task 1 details", HighPriority, SingleTask, false, false);
    // RepeatedTask for today
    std::array<bool, 7> repeatDays = {false, true, false, false, false, false, false}; // Repeat on Tuesday
    TaskData task2(QDateTime(QDate::currentDate(), QTime(10, 0)), QDateTime(QDate::currentDate(), QTime(11, 0)), "Repeated Task 1", "Repeated Task 1 details", MediumPriority, RepeatedTask, false, false, repeatDays);

    std::array<bool, 7> RepeatDays = {true, true, false, false, false, false, false}; // Repeat on Tuesday
    TaskData task7(QDateTime(QDate::currentDate(), QTime(10, 0)), QDateTime(QDate::currentDate(), QTime(11, 0)), "Repeated Task 2", "Repeated Task 1 details", MediumPriority, RepeatedTask, false, false, RepeatDays);
    // DeadlineTask for today
    TaskData task3(QDateTime(QDate::currentDate(), QTime(12, 0)), QDateTime(QDate::currentDate(), QTime(19, 0)), "Deadline Task 1", "Deadline Task 1 details", LowPriority, DeadlineTask, false, false);

    // Insert tasks into the database
    db.insertTaskData(task1);
    db.insertTaskData(task2);
    db.insertTaskData(task3);
    db.insertTaskData(task7);

    // SingleTask for tomorrow
    TaskData task4(QDateTime(QDate::currentDate().addDays(1), QTime(8, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(9, 0)), "Single Task 2", "Single Task 2 details", HighPriority, SingleTask, false, false);

    // RepeatedTask for tomorrow
    std::array<bool, 7> repeatDaysTomorrow = {false, false, true, false, false, false, false}; // Repeat on Wednesday
    TaskData task5(QDateTime(QDate::currentDate().addDays(1), QTime(10, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(11, 0)), "Repeated Task 2", "Repeated Task 2 details", MediumPriority, RepeatedTask, false, false, repeatDaysTomorrow);

    // DeadlineTask for tomorrow
    TaskData task6(QDateTime(QDate::currentDate().addDays(1), QTime(12, 0)), QDateTime(QDate::currentDate().addDays(1), QTime(13, 0)), "Deadline Task 2", "Deadline Task 2 details", LowPriority, DeadlineTask, false, false);

    // Insert tasks into the database
    db.insertTaskData(task4);
    db.insertTaskData(task5);
    db.insertTaskData(task6);
    db.removeDuplicateTasks();
    db.queryTaskData();
    QVector<TaskData> tasks = db.findTaskDataByDate(QDate::currentDate());

    // 打印查询结果
    qDebug() << "Tasks found for TaskType 0 and date " << QDate::currentDate().toString("yyyy-MM-dd") << ":";

    for (const auto &task : tasks) {
        qDebug() << "Task Name: " << task.name()
                 << ", Start Time: " << task.startTime().toString("yyyy-MM-dd HH:mm:ss");
    }

    int windowWidth = 800;
    int windowHeight = 800;
    qreal stride = 48.0;

    TimeAxis timeAxis(windowWidth, windowHeight, stride);
    timeAxis.drawDayTasks();
    timeAxis.show();

*/



//Task修改代码测试
// Task t;
// t.show();
// std::array<bool, 7> repeatDays = {true,true,false,true,false,true,true};
// TaskData task(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(3600),
//               "任务1", "这是任务1的详细描述", HighPriority, SingleTask, true, false,repeatDays);
// t.setTaskData(task);
// TaskData newTask(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(7200),
//                  "修改后的任务1", "这是修改后的任务1的详细描述", LowPriority, RepeatedTask, false, true, repeatDays);
// db.insertTaskData(task);
// db.queryTaskData();
// db.modifyTaskData(task,newTask);
// db.queryTaskData();
// db.deleteTaskData(newTask);
// db.queryTaskData();
// //关闭数据库
// db.clearTable("task_data_table");
//db.dropTable("task_data_table");



//时间轴代码测试
/*    int windowWidth = 400;
        int windowHeight = 600;
        qreal stride = 24.0;

        TimeAxis timeAxis(windowWidth, windowHeight, stride);
        timeAxis.show();

        // 创建任务数据对象
        TaskData task(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(3600),
                      "任务1", "这是任务1的详细描述", LowPriority, SingleTask, true, false);

        // 添加任务组件到时间轴
        timeAxis.addTaskWidget(task);

        // //查看数据情况

        // int windowWidth = 800;
        // int windowHeight = 800;
        // qreal stride = 48.0;

        // TimeAxis timeAxis(windowWidth, windowHeight, stride);
        // timeAxis.show();

        // // 创建任务数据对象
        // TaskData task(QDateTime::currentDateTime().addSecs(1000), QDateTime::currentDateTime().addSecs(3600),
        //               "任务1", "这是任务1的详细描述", LowPriority, SingleTask, true, false);
        // db.clearTable("task_data_table");
        // db.insertTaskData(task);
        // db.queryTaskData();
        // // 添加任务组件到时间轴
        // timeAxis.addTaskWidget(task);

    */




//数据库代码测试
// MyDataBase db;
// if (!db.openDb())
// {
//     qDebug()<<"error";
//     return -1;
// }
// db.createTable();
// db.resetAutoIncrement("task_data_table");
// QDateTime startTime = QDateTime::currentDateTime();
// QDateTime endTime = QDateTime::currentDateTime().addSecs(3600); // 结束时间设置为当前时间后 1 小时

// // 设置任务名称和详细描述
// QString name = "任务1";
// QString detail = "这是任务1的详细描述";

// // 设置优先级和任务类型
// Priority priority = MediumPriority;
// TaskType type = SingleTask;

// // 设置任务状态
// bool is_done = true;
// bool overdue = true;

// // 设置重复日数组 (例如：每周一、周三和周五)
// std::array<bool, 7> repeatDays = {false, true, false, true, false, true, false};

// // 创建任务对象并初始化所有属性
// TaskData task(startTime, endTime, name, detail, priority, type, is_done, overdue, repeatDays);

// db.insertTaskData(task);
// db.queryTaskData();
// db.clearTable("task_data_table");
// //db.dropTable("task_data_table");
// db.closeDb();
