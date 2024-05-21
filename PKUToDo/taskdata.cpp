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



