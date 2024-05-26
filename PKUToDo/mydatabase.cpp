 #include "mydatabase.h"

MyDataBase::MyDataBase() {
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");//检查是否已有链接
    }
    else{
        // 建立和SQlite数据库的连接，只建立链接，不会重新创建
        database = QSqlDatabase::addDatabase("QSQLITE");
        //设置保存地址，确保数据保存
        QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir dir(dbPath);
        qDebug() << "App data location:" << dbPath;
        if (!dir.exists())
        {
            dir.mkpath(".");
        }
        // 设置数据库文件的名字，若存在则不会再次创建而是直接打开！注意！！
        database.setDatabaseName("MyDataBase.db");
    }
}

bool MyDataBase::openDb()
{
    if(database.isOpen()) {
        qDebug()<<"isOpened()";
        return true;}
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
        return false;
    }
    else
    {
        qDebug()<<"DataBase successfully opened";
    }

    return true;
}

void MyDataBase::createTable()
{
    QSqlQuery sqlQuery;
    //创建针对计划存储的表
    sqlQuery.prepare("CREATE TABLE IF NOT EXISTS task_data_table ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "taskname TEXT, "
                  "taskdetails TEXT, "
                  "type INTEGER,"
                  "priority INTEGER, "
                  "start_time DATETIME, "
                  "end_time DATETIME, "
                  "is_done INTEGER, "
                  "overdue INTEGER, "
                  "repeat_days INTEGER)");
    if(!sqlQuery.exec()){
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else{
        qDebug() << "TaskTable created!";
    }
    //创建代办事项的表
    sqlQuery.prepare("CREATE TABLE IF NOT EXISTS todo_data_table ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "name TEXT, "
                     "duration INTEGER, "
                     "priority INTEGER, "
                     "is_done INTEGER)");

    if(!sqlQuery.exec()){
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    }
    else{
        qDebug() << "ToDoTable created!";
    }

    QString createTableSQL = "CREATE TABLE IF NOT EXISTS statistic_table ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "task_name TEXT, "
                             "start_time DATETIME, "
                             "end_time DATETIME"
                             ");";

    // 执行 SQL 查询来创建新表格
    if (!sqlQuery.exec(createTableSQL)) {
        qDebug() << "Error: Fail to create table. " << sqlQuery.lastError();
    } else {
        qDebug() << "statistic table created!";
    }
}

bool MyDataBase::isTableExist(QString &tableName)
{
    if(database.tables().contains(tableName))
    {
        return true;
    }

    return false;
}
//清空数据表
void MyDataBase::clearTable(const QString &tableName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM " + tableName);

    if (!query.exec()) {
        qDebug() << "Error: Failed to clear table '" << tableName << "'. " << query.lastError();
    } else {
        qDebug() << "Table '" << tableName << "' cleared successfully!";
    }
}
//删除数据表
void MyDataBase::dropTable(const QString &tableName)
{
    QSqlQuery query;
    query.prepare("DROP TABLE " + tableName);

    if (!query.exec()) {
        qDebug() << "Error: Failed to drop table '" << tableName << "'. " << query.lastError();
    } else {
        qDebug() << "Table '" << tableName << "' dropped successfully!";
    }
}
//清空自增id序列
void MyDataBase::resetAutoIncrement(const QString &tableName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM sqlite_sequence WHERE name = :tableName");
    query.bindValue(":tableName", tableName);

    if (!query.exec()) {
        qDebug() << "Error: Failed to reset auto-increment for table '" << tableName << "'. " << query.lastError();
    } else {
        qDebug() << "Auto-increment reset for table '" << tableName << "' successfully!";
    }
}
//关闭数据库
void MyDataBase::closeDb(void)
{
    database.close();
}



//针对task_data_table的函数///////////////////////////////////////////////////////////////////////////////////

void MyDataBase::insertTaskData(const TaskData &taskData) {
    QSqlQuery query;
    query.prepare("INSERT INTO task_data_table (taskname, taskdetails, type , priority, start_time, end_time, is_done, overdue, repeat_days) "
                  "VALUES (:taskname, :taskdetails, :type , :priority, :start_time, :end_time, :is_done, :overdue, :repeat_days)");
    query.bindValue(":taskname", taskData.name());
    query.bindValue(":taskdetails", taskData.detail());
    query.bindValue(":type", static_cast<int>(taskData.type()));
    //qDebug()<<"typeValue"<<static_cast<int>(taskData.type());
    query.bindValue(":priority", static_cast<int>(taskData.priority()));
    query.bindValue(":start_time", taskData.startTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":end_time", taskData.endTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":is_done", taskData.isDone() ? 1 : 0);
    query.bindValue(":overdue", taskData.isOverdue() ? 1 : 0);
    query.bindValue(":repeat_days", taskData.repeatDaysToInt());

    qDebug() << "Task Name Parameter: " << query.boundValue(":taskname");
    qDebug() << "Task Details Parameter: " << query.boundValue(":taskdetails");
    qDebug() << "Type Parameter: " << query.boundValue(":type");
    qDebug() << "Priority Parameter: " << query.boundValue(":priority");
    qDebug() << "Start Time Parameter: " << query.boundValue(":start_time");
    qDebug() << "End Time Parameter: " << query.boundValue(":end_time");
    qDebug() << "Is Done Parameter: " << query.boundValue(":is_done");
    qDebug() << "Overdue Parameter: " << query.boundValue(":overdue");
    qDebug() << "repeatDay Parameter: " << query.boundValue(":repeat_days");
    if (!query.exec()) {
        qDebug() << "Error: Failed to insert data. " << query.lastError();
    } else {
        qDebug() << "Data inserted successfully!";
    }
}


void MyDataBase::deleteTaskData(int taskId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM task_data_table WHERE id = :id");
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        qDebug() << "Error: Failed to delete data. " << query.lastError();
    } else {
        qDebug() << "Data deleted successfully!";
    }
}

void MyDataBase::modifyTaskData(const TaskData &taskData, int taskId)
{
    QSqlQuery query;
    query.prepare("UPDATE task_data_table SET taskname = :taskname, taskdetails = :taskdetails, type = :type, priority = :priority, "
                  "start_time = :start_time, end_time = :end_time, is_done = :is_done, overdue = :overdue ,repeat_days = :repeat_days"
                  "WHERE id = :id");
    query.bindValue(":taskname", taskData.name());
    query.bindValue(":taskdetails", taskData.detail());
    query.bindValue(":type", static_cast<int>(taskData.type()));
    query.bindValue(":priority", static_cast<int>(taskData.priority()));
    query.bindValue(":start_time", taskData.startTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":end_time", taskData.endTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":is_done", taskData.isDone() ? 1 : 0);
    query.bindValue(":overdue", taskData.isOverdue() ? 1 : 0);
    query.bindValue(":repeat_days", taskData.repeatDaysToInt());
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        qDebug() << "Error: Failed to modify data. " << query.lastError();
    } else {
        qDebug() << "Data modified successfully!";
    }
}

void MyDataBase::deleteTaskData(const TaskData &taskData)
{
    QSqlQuery query;
    query.prepare("DELETE FROM task_data_table WHERE taskname = :taskname AND taskdetails = :taskdetails AND type = :type AND priority = :priority "
                  "AND start_time = :start_time AND end_time = :end_time AND is_done = :is_done AND overdue = :overdue AND repeat_days = :repeat_days");
    query.bindValue(":taskname", taskData.name());
    query.bindValue(":taskdetails", taskData.detail());
    query.bindValue(":type", static_cast<int>(taskData.type()));
    query.bindValue(":priority", static_cast<int>(taskData.priority()));
    query.bindValue(":start_time", taskData.startTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":end_time", taskData.endTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":is_done", taskData.isDone() ? 1 : 0);
    query.bindValue(":overdue", taskData.isOverdue() ? 1 : 0);
    query.bindValue(":repeat_days", taskData.repeatDaysToInt());

    if (!query.exec()) {
        qDebug() << "Error: Failed to delete data. " << query.lastError();
    } else {
        qDebug() << "Data deleted successfully!";
    }
}

void MyDataBase::modifyTaskData(const TaskData &taskData, const TaskData &newTaskData)
{
    QSqlQuery query;
    query.prepare("UPDATE task_data_table SET taskname = :new_taskname, taskdetails = :new_taskdetails, type = :new_type, priority = :new_priority, "
                  "start_time = :new_start_time, end_time = :new_end_time, is_done = :new_is_done, overdue = :new_overdue, repeat_days = :new_repeat_days "
                  "WHERE taskname = :taskname AND taskdetails = :taskdetails AND type = :type AND priority = :priority AND start_time = :start_time AND "
                  "end_time = :end_time AND is_done = :is_done AND overdue = :overdue AND repeat_days = :repeat_days");
    query.bindValue(":new_taskname", newTaskData.name());
    query.bindValue(":new_taskdetails", newTaskData.detail());
    query.bindValue(":new_type", static_cast<int>(newTaskData.type()));
    query.bindValue(":new_priority", static_cast<int>(newTaskData.priority()));
    query.bindValue(":new_start_time", newTaskData.startTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":new_end_time", newTaskData.endTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":new_is_done", newTaskData.isDone() ? 1 : 0);
    query.bindValue(":new_overdue", newTaskData.isOverdue() ? 1 : 0);
    query.bindValue(":new_repeat_days", newTaskData.repeatDaysToInt());
     qDebug() << "New Task Name Parameter: " << query.boundValue(":new_taskname");



    query.bindValue(":taskname", taskData.name());
    query.bindValue(":taskdetails", taskData.detail());
    query.bindValue(":type", static_cast<int>(taskData.type()));
    query.bindValue(":priority", static_cast<int>(taskData.priority()));
    query.bindValue(":start_time", taskData.startTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":end_time", taskData.endTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":is_done", taskData.isDone() ? 1 : 0);
    query.bindValue(":overdue", taskData.isOverdue() ? 1 : 0);
    query.bindValue(":repeat_days", taskData.repeatDaysToInt());
    qDebug() << "Task Name Parameter: " << query.boundValue(":taskname");

    if (!query.exec()) {
        qDebug() << "Error: Failed to modify data. " << query.lastError();
    } else {
        qDebug() << "Data modified successfully!";
    }
}


void MyDataBase::queryTaskData() {
    qDebug()<<"queryTaskData";
    QSqlQuery sqlQuery("SELECT * FROM task_data_table");
    while (sqlQuery.next()) {
        int id = sqlQuery.value("id").toInt();
        QDateTime startTime = sqlQuery.value("start_time").toDateTime();
        QDateTime endTime = sqlQuery.value("end_time").toDateTime();
        QString name = sqlQuery.value("taskname").toString();
        QString detail = sqlQuery.value("taskdetails").toString();
        TaskType type = static_cast<TaskType>(sqlQuery.value("type").toInt());
        Priority priority = static_cast<Priority>(sqlQuery.value("priority").toInt());
        bool isDone = sqlQuery.value("is_done").toInt() == 1;
        bool isOverdue = sqlQuery.value("overdue").toInt() == 1;
        int repeatDays = sqlQuery.value("repeat_days").toInt();

        //TaskData task(startTime, endTime, name, detail, priority, RepeatedTask, isDone, isOverdue);
        //task.setRepeatDaysFromInt(repeatDays);

        qDebug() << "ID:" << id
                 << ", Start Time:" << startTime.toString("yyyy-MM-dd HH:mm:ss")
                 << ", End Time:" << endTime.toString("yyyy-MM-dd HH:mm:ss")
                 << ", Name:" << name
                 << ", Detail:" << detail
                 << ", Type:"  <<type
                 << ", Priority:" << static_cast<int>(priority)
                 << ", Is Done:" << isDone
                 << ", Is Overdue:" << isOverdue
                 << ", Repeat Days:" << repeatDays;
    }
}

QList<TaskData> MyDataBase::findTaskData(const QString &taskName, const QDate &startDate, const QDate &endDate, Priority priority)
{
    QList<TaskData> taskList;
    QSqlQuery query;

    // 构建查询条件字符串
    QString condition = "1=1"; // 确保基础条件总是为真，便于后续添加条件
    if (!taskName.isEmpty()) {
        condition += QString(" AND taskname LIKE '%%1%'").arg(taskName);
    }
    if (startDate.isValid()) {
        condition += QString(" AND start_time >= '%1'").arg(startDate.toString("yyyy-MM-dd"));
    }
    if (endDate.isValid()) {
        condition += QString(" AND end_time <= '%1'").arg(endDate.toString("yyyy-MM-dd"));
    }
    if (priority == HighPriority||priority == MediumPriority||priority == LowPriority) { // 假设 Priority::None 表示不筛选优先级
        condition += QString(" AND priority = %1").arg(static_cast<int>(priority));
    }

    QString queryString = "SELECT * FROM task_data_table WHERE " + condition;
    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query. " << query.lastError();
        return taskList;
    }

    while (query.next()) {
        QDateTime startTime = query.value("start_time").toDateTime();
        QDateTime endTime = query.value("end_time").toDateTime();
        QString name = query.value("taskname").toString();
        QString detail = query.value("taskdetails").toString();
        TaskType type = static_cast<TaskType>(query.value("type").toInt());
        Priority priority = static_cast<Priority>(query.value("priority").toInt());
        bool isDone = query.value("is_done").toInt() == 1;
        bool isOverdue = query.value("overdue").toInt() == 1;
        int repeatDays = query.value("repeat_days").toInt();

        TaskData task(startTime, endTime, name, detail, priority, type, isDone, isOverdue);
        task.setRepeatDaysFromInt(repeatDays);
        taskList.append(task);
    }

    return taskList;
}





//严格匹配
QList<TaskData> MyDataBase::findTaskData(const QString &condition)
{
    QList<TaskData> taskList;
    QSqlQuery query;
    QString queryString = "SELECT * FROM task_data_table WHERE " + condition;
    query.prepare(queryString);
    qDebug()<<"target condition"<<condition;
    if (!query.exec())
    {
        qDebug() << "Error: Failed to execute query. " << query.lastError();
        return taskList;
    }
    int rowCount=0;
    while (query.next())
    {
        rowCount++;
        QDateTime startTime = query.value("start_time").toDateTime();
        QDateTime endTime = query.value("end_time").toDateTime();
        QString name = query.value("taskname").toString();
        QString detail = query.value("taskdetails").toString();
        TaskType type = static_cast<TaskType>(query.value("type").toInt());
        Priority priority = static_cast<Priority>(query.value("priority").toInt());
        bool isDone = query.value("is_done").toInt() == 1;
        bool isOverdue = query.value("overdue").toInt() == 1;
        int repeatDays = query.value("repeat_days").toInt();

        TaskData task(startTime, endTime, name, detail, priority, type, isDone, isOverdue);
        task.setRepeatDaysFromInt(repeatDays);
        taskList.append(task);
    }
    qDebug()<<"findCount"<<rowCount;
    return taskList;
}

QList<TaskData> MyDataBase::findTaskDataByDate(const QDate &date)
{

    // 单次类型的查询条件
    QString singleCondition = QString("type = 0 AND DATE(start_time) <= '%1' AND DATE(end_time) >= '%1'")
                                  .arg(date.toString("yyyy-MM-dd"));

    // 重复类型的查询条件
    int dayOfWeek = date.dayOfWeek();
    qDebug()<<dayOfWeek;
    QString repeatCondition = QString("type = 1 AND (repeat_days & %1) > 0 AND DATE(start_time) <= '%2' AND DATE(end_time) >= '%2'")
                                  .arg(1 << (dayOfWeek - 1)) // 将整数转换为字符串应该放在后面
                                  .arg(date.toString("yyyy-MM-dd"));
    // 截至日期型的查询条件
    QString deadlineCondition = QString("type = 2 AND DATE(end_time) = '%1'").arg(date.toString("yyyy-MM-dd"));

    // 组合查询条件
    QString combinedCondition = QString("(%1) OR (%2) OR (%3)").arg(singleCondition).arg(repeatCondition).arg(deadlineCondition);

    return MyDataBase::findTaskData(combinedCondition);
}
//去重函数
void MyDataBase::removeDuplicateTasks() {
    QSqlQuery query;

    // 查询重复的记录
    QString duplicateQuery = R"(
        DELETE FROM task_data_table
        WHERE rowid NOT IN (
            SELECT MIN(rowid)
            FROM task_data_table
            GROUP BY start_time, end_time, taskname, taskdetails, type, priority, is_done, overdue, repeat_days
        )
    )";

    query.prepare(duplicateQuery);

    if (!query.exec()) {
        qDebug() << "Error: Failed to remove duplicate tasks. " << query.lastError();
    } else {
        qDebug() << "Duplicate tasks removed successfully.";
    }
}


//Todo类的相关操作函数//////////////////////////////////////////////////////////////

void MyDataBase::insertToDoData(const ToDoData &toDoData) {
    QSqlQuery query;
    query.prepare("INSERT INTO todo_data_table (name, duration, priority, is_done) "
                  "VALUES (:name, :duration, :priority, :is_done)");
    query.bindValue(":name", toDoData.name());
    query.bindValue(":duration", toDoData.expectTime()); // 使用 toString("hh:mm:ss") 表示持续时间
    query.bindValue(":priority", static_cast<int>(toDoData.priority()));
    query.bindValue(":is_done", toDoData.isDone() ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "Error: Failed to insert ToDo data. " << query.lastError();
    } else {
        qDebug() << "ToDo data inserted successfully!";
    }
}

void MyDataBase::modifyToDoData(const ToDoData &toDoData, int toDoId) {
    QSqlQuery query;
    query.prepare("UPDATE todo_data_table SET name = :name, duration = :duration, priority = :priority, is_done = :is_done "
                  "WHERE id = :id");
    query.bindValue(":name", toDoData.name());
    query.bindValue(":duration", toDoData.expectTime()); // 使用 toString("hh:mm:ss") 表示持续时间
    query.bindValue(":priority", static_cast<int>(toDoData.priority()));
    query.bindValue(":is_done", toDoData.isDone() ? 1 : 0);
    query.bindValue(":id", toDoId);

    if (!query.exec()) {
        qDebug() << "Error: Failed to modify ToDo data. " << query.lastError();
    } else {
        qDebug() << "ToDo data modified successfully!";
    }
}

void MyDataBase::deleteToDoData(const ToDoData &toDoData) {
    QSqlQuery query;
    query.prepare("DELETE FROM todo_data_table WHERE name = :name AND duration = :duration AND priority = :priority AND is_done = :is_done");
    query.bindValue(":name", toDoData.name());
    query.bindValue(":duration", toDoData.expectTime()); // 使用 toString("hh:mm:ss") 表示持续时间
    query.bindValue(":priority", static_cast<int>(toDoData.priority()));
    query.bindValue(":is_done", toDoData.isDone() ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "Error: Failed to delete ToDo data. " << query.lastError();
    } else {
        qDebug() << "ToDo data deleted successfully!";
    }
}

void MyDataBase::modifyToDoData(const ToDoData &toDoData, const ToDoData &newToDoData) {
    QSqlQuery query;
    query.prepare("UPDATE todo_data_table SET name = :new_name, duration = :new_duration, priority = :new_priority, is_done = :new_is_done "
                  "WHERE name = :name AND duration = :duration AND priority = :priority AND is_done = :is_done");
    query.bindValue(":new_name", newToDoData.name());
    query.bindValue(":new_duration", newToDoData.expectTime());
    query.bindValue(":new_priority", static_cast<int>(newToDoData.priority()));
    query.bindValue(":new_is_done", newToDoData.isDone() ? 1 : 0);

    query.bindValue(":name", toDoData.name());
    query.bindValue(":duration", toDoData.expectTime());
    query.bindValue(":priority", static_cast<int>(toDoData.priority()));
    query.bindValue(":is_done", toDoData.isDone() ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "Error: Failed to modify ToDo data. " << query.lastError();
    } else {
        qDebug() << "ToDo data modified successfully!";
    }
}

QList<ToDoData> MyDataBase::findToDoData(const QString &condition) {
    QList<ToDoData> toDoList;
    QSqlQuery query;
    QString queryString = "SELECT * FROM todo_data_table WHERE " + condition;
    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query. " << query.lastError();
        return toDoList;
    }

    int rowCount = 0;
    while (query.next()) {
        rowCount++;
        QString name = query.value("name").toString();
        int duration = query.value("duration").toInt(); //
        Priority priority = static_cast<Priority>(query.value("priority").toInt());
        bool isDone = query.value("is_done").toInt() == 1;

        ToDoData toDoData(name, duration, priority); // 传入持续时间参数
        toDoData.setIsDone(isDone);
        toDoList.append(toDoData);
    }
    qDebug() << "Find count"<< rowCount;
    return toDoList;
}

void MyDataBase::removeDuplicateToDoData() {
    QSqlQuery query;

    // 查询重复的记录
    QString duplicateQuery = R"(
        DELETE FROM todo_data_table
        WHERE rowid NOT IN (
            SELECT MIN(rowid)
            FROM todo_data_table
            GROUP BY name, duration, priority, is_done
        )
    )";

    query.prepare(duplicateQuery);

    if (!query.exec()) {
        qDebug() << "Error: Failed to remove duplicate ToDo data. " << query.lastError();
    } else {
        qDebug() << "Duplicate ToDo data removed successfully.";
    }
}

void MyDataBase::queryToDoData() {
    qDebug() << "queryToDoData";
    QSqlQuery sqlQuery("SELECT * FROM todo_data_table");
    while (sqlQuery.next()) {
        int id = sqlQuery.value("id").toInt();
        QString name = sqlQuery.value("name").toString();
        int duration = sqlQuery.value("duration").toInt();
        Priority priority = static_cast<Priority>(sqlQuery.value("priority").toInt());
        bool isDone = sqlQuery.value("is_done").toInt() == 1;

        ToDoData todoData(name, duration, priority, isDone);

        qDebug() << "ID:" << id
                 << ", Name:" << todoData.name()
                 << ", Duration (seconds):" << todoData.expectTime()
                 << ", Priority:" << static_cast<int>(todoData.priority())
                 << ", Is Done:" << todoData.isDone();
    }
}

///针对统计数据的函数/////////////////////////////////////////////
void MyDataBase::insertStatisticData(const StatisticData &statisticData) {
    QSqlQuery query;
    query.prepare("INSERT INTO statistic_table (task_name, start_time, end_time) "
                  "VALUES (:task_name, :start_time, :end_time)");
    query.bindValue(":task_name", statisticData.name());
    query.bindValue(":start_time", statisticData.startTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":end_time", statisticData.endTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        qDebug() << "Error: Failed to insert Statistic data. " << query.lastError();
    } else {
        qDebug() << "Statistic data inserted successfully!";
    }
}

void MyDataBase::modifyStatisticData(const StatisticData &statisticData, const StatisticData &newStatisticData) {
    QSqlQuery query;
    query.prepare("UPDATE statistic_table SET task_name = :new_task_name, start_time = :new_start_time, end_time = :new_end_time "
                  "WHERE task_name = :task_name AND start_time = :start_time AND end_time = :end_time");
    query.bindValue(":new_task_name", newStatisticData.name());
    query.bindValue(":new_start_time", newStatisticData.startTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":new_end_time", newStatisticData.endTime().toString("yyyy-MM-dd hh:mm:ss"));

    query.bindValue(":task_name", statisticData.name());
    query.bindValue(":start_time", statisticData.startTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":end_time", statisticData.endTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        qDebug() << "Error: Failed to modify Statistic data. " << query.lastError();
    } else {
        qDebug() << "Statistic data modified successfully!";
    }
}

QList<StatisticData> MyDataBase::findStatisticData(const QString &condition) {
    QList<StatisticData> statisticList;
    QSqlQuery query;
    QString queryString = "SELECT * FROM statistic_table WHERE " + condition;
    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query. " << query.lastError();
        return statisticList;
    }

    int rowCount = 0;
    while (query.next()) {
        rowCount++;
        QString name = query.value("task_name").toString();
        QDateTime startTime = query.value("start_time").toDateTime();
        QDateTime endTime = query.value("end_time").toDateTime();

        StatisticData statisticData(name, startTime, endTime);
        statisticList.append(statisticData);
    }
    qDebug() << "Find count"<< rowCount;
    return statisticList;
}

QList<StatisticData> MyDataBase::findStatisticDataBetween(const QDateTime &startTime, const QDateTime &endTime) {
    QList<StatisticData> statisticList;
    QSqlQuery query;
    query.prepare("SELECT * FROM statistic_table WHERE start_time >= :start_time AND end_time <= :end_time");
    query.bindValue(":start_time", startTime);
    query.bindValue(":end_time", endTime);

    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query. " << query.lastError();
        return statisticList;
    }

    int rowCount = 0;
    while (query.next()) {
        rowCount++;
        QString name = query.value("task_name").toString();
        QDateTime start = query.value("start_time").toDateTime();
        QDateTime end = query.value("end_time").toDateTime();

        StatisticData statisticData(name, start, end);
        statisticList.append(statisticData);
    }
    qDebug() << "Found count: " << rowCount;
    return statisticList;
}
QList<StatisticData> MyDataBase::classifyAndCalculateTotalTime(const QList<StatisticData> &dataList) {
    QList<StatisticData> result;

    // 分类统计
    QMap<QString, int> totalTimeMap; // 按照名称分类的总时间映射表
    foreach (const StatisticData &data, dataList) {
        if (!totalTimeMap.contains(data.name())) {
            totalTimeMap.insert(data.name(), 0);
        }
        int duration = data.startTime().secsTo(data.endTime()); // 计算时间间隔（秒）
        totalTimeMap[data.name()] += duration;
    }

    // 转换为结果列表
    foreach (const QString &name, totalTimeMap.keys()) {
        StatisticData newData(name);
        newData.setCount(totalTimeMap.value(name) / 3600); // 将秒转换为小时
        result.append(newData);
    }

    return result;
}


void MyDataBase::deleteStatisticData(const StatisticData &statisticData) {
    QSqlQuery query;
    query.prepare("DELETE FROM statistic_table WHERE task_name = :task_name AND start_time = :start_time AND end_time = :end_time");
    query.bindValue(":task_name", statisticData.name());
    query.bindValue(":start_time", statisticData.startTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":end_time", statisticData.endTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        qDebug() << "Error: Failed to delete Statistic data. " << query.lastError();
    } else {
        qDebug() << "Statistic data deleted successfully!";
    }
}

void MyDataBase::queryStatisticData() {
    qDebug() << "queryStatisticData";
    QSqlQuery sqlQuery("SELECT * FROM statistic_table");
    while (sqlQuery.next()) {
        int id = sqlQuery.value("id").toInt();
        QString name = sqlQuery.value("task_name").toString();
        QDateTime startTime = sqlQuery.value("start_time").toDateTime();
        QDateTime endTime = sqlQuery.value("end_time").toDateTime();

        StatisticData statisticData(name, startTime, endTime);

        qDebug() << "ID:" << id
                 << ", Task Name:" << statisticData.name()
                 << ", Start Time:" << statisticData.startTime().toString("yyyy-MM-dd hh:mm:ss")
                 << ", End Time:" << statisticData.endTime().toString("yyyy-MM-dd hh:mm:ss");
    }
}


