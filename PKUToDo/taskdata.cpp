#include "taskdata.h"
//这是Task的数据文件，addTask的界面文件中会创建一个TaskData存入数据库
TaskData::TaskData(const QDateTime &startTime, const QDateTime &endTime,
                   const QString &name, const QString &detail, Priority priority,
                   TaskType type, bool is_done, bool overdue, const std::array<bool, 7>& repeatDays)
    : m_startTime(startTime), m_endTime(endTime), m_name(name), m_detail(detail),
    m_priority(priority), m_type(type), is_done(is_done), overdue(overdue), m_repeatDays(repeatDays) {
}

//以下是访问私有对象的一些接口
QDateTime TaskData::startTime() const {
    return m_startTime;
}

void TaskData::setStartTime(const QDateTime &startTime) {
    m_startTime = startTime;
}

QDateTime TaskData::endTime() const {
    return m_endTime;
}

void TaskData::setEndTime(const QDateTime &endTime) {
    m_endTime = endTime;
}

QString TaskData::name() const {
    return m_name;
}

void TaskData::setName(const QString &detail) {
    m_name = detail;
}
QString TaskData::detail() const {
    return m_detail;
}

void TaskData::setDetail(const QString &detail) {
    m_detail = detail;
}

Priority TaskData::priority() const {
    return m_priority;
}

void TaskData::setPriority(Priority priority) {
    m_priority = priority;
}

TaskType TaskData::type() const {
    return m_type;
}

void TaskData::setType(TaskType type) {
    m_type = type;
}

bool TaskData::isDone() const
{
    return is_done;
}

void TaskData::setDone(bool done)
{
    is_done = done;
}

bool TaskData::isOverdue() const
{
    return overdue;
}

void TaskData::setOverdue(bool due)
{
    overdue = due;
}

std::array<bool, 7> TaskData::getRepeatDays() const {
    return m_repeatDays;
}

void TaskData::setRepeatDays(const std::array<bool, 7>& repeatDays) {
    m_repeatDays = repeatDays;
}

//通过位运算存储重复型计划数据，转化成一个整数
int TaskData::repeatDaysToInt() const {
    int result = 0;
    for (int i = 0; i < 7; ++i) {
        if (m_repeatDays[i]) {
            result |= (1 << i);
        }
    }
    return result;
}

void TaskData::setRepeatDaysFromInt(int repeatDays) {
    for (int i = 0; i < 7; ++i) {
        m_repeatDays[i] = (repeatDays & (1 << i)) != 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////

ToDoData::ToDoData(const QString &name,const int& expectTime, Priority priority, bool isDone)
    : m_name(name), m_expectTime(expectTime), m_priority(priority), m_isDone(isDone) {}

QString ToDoData::name() const {
    return m_name;
}

void ToDoData::setName(const QString &name) {
    m_name = name;
}

int ToDoData::expectTime() const {
    return m_expectTime;
}

void ToDoData::setExpectTime(const int& expectTime) {
    m_expectTime = expectTime;
}

Priority ToDoData::priority() const {
    return m_priority;
}

void ToDoData::setPriority(Priority priority) {
    m_priority = priority;
}

bool ToDoData::isDone() const {
    return m_isDone;
}

void ToDoData::setIsDone(bool isDone) {
    m_isDone = isDone;
}

///////////////////////////////////////////////////////////////////////////////

StatisticData::StatisticData(const QString &name, const QDateTime &startTime,
                             const QDateTime &endTime, const int &count)
    : m_name(name), m_startTime(startTime), m_endTime(endTime), m_count(count) {}

QString StatisticData::name() const {
    return m_name;
}

void StatisticData::setName(const QString &name) {
    m_name = name;
}

QDateTime StatisticData::startTime() const {
    return m_startTime;
}

void StatisticData::setStartTime(const QDateTime &startTime) {
    m_startTime = startTime;
}

QDateTime StatisticData::endTime() const {
    return m_endTime;
}

void StatisticData::setEndTime(const QDateTime &endTime) {
    m_endTime = endTime;
}

qreal StatisticData::count() const {
    return m_count;
}

void StatisticData::setCount(const qreal &count) {
    m_count = count;
}

