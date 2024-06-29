#ifndef TASKDATA_H
#define TASKDATA_H

#include <QDateTime>
#include <QString>
#include <array>
//优先级有三等
enum Priority {
    HighPriority,
    MediumPriority,
    LowPriority,
    None
};
//类型暂定有三种
enum TaskType {
    SingleTask,
    RepeatedTask,
    DeadlineTask
};

class TaskData {
public:
    TaskData(const QDateTime &startTime = QDateTime(), const QDateTime &endTime = QDateTime(),
             const QString &name = "", const QString &detail = "", Priority priority = MediumPriority,
             TaskType type = SingleTask, bool is_done = false, bool overdue = false,
             const std::array<bool, 7>& repeatDays = {false, false, false, false, false, false, false});

    QDateTime startTime() const;
    void setStartTime(const QDateTime &startTime);

    QDateTime endTime() const;
    void setEndTime(const QDateTime &endTime);

    QString name() const;
    void setName(const QString &detail);
    QString detail() const;
    void setDetail(const QString &detail);

    Priority priority() const;
    void setPriority(Priority priority);

    TaskType type() const;
    void setType(TaskType type);

    bool isDone() const;
    void setDone(bool done);

    bool isOverdue() const;
    void setOverdue(bool due);


    std::array<bool, 7> getRepeatDays() const;
    void setRepeatDays(const std::array<bool, 7>& repeatDays);

    int repeatDaysToInt() const;
    void setRepeatDaysFromInt(int repeatDays);
private:
    QDateTime m_startTime;
    QDateTime m_endTime;
    QString m_name;
    QString m_detail;
    Priority m_priority;
    TaskType m_type;
    bool is_done=false;
    bool overdue=false;
    std::array<bool, 7> m_repeatDays;
};

///////////////////////////////////////////////////////////////////////////////

class ToDoData {
public:
    ToDoData(const QString &name = "", const int &expectTime = 0,
             Priority priority = MediumPriority, bool isDone = false);

    QString name() const;
    void setName(const QString &name);

    int expectTime() const;
    void setExpectTime(const int &expectTime);

    Priority priority() const;
    void setPriority(Priority priority);

    bool isDone() const;
    void setIsDone(bool isDone);

private:
    QString m_name;
    int m_expectTime;
    Priority m_priority;
    bool m_isDone;
};

///////////////////////////////////////////////////////////////////////////////////

class StatisticData {
public:
    StatisticData(const QString &name = "", const QDateTime &startTime = QDateTime(),
                  const QDateTime &endTime = QDateTime(), const int &count = 0);

    QString name() const;
    void setName(const QString &name);

    QDateTime startTime() const;
    void setStartTime(const QDateTime &startTime);

    QDateTime endTime() const;
    void setEndTime(const QDateTime &endTime);

    qreal count() const;
    void setCount(const qreal &count);

    qreal day_count(const QDate &date) const;

private:
    QString m_name;
    QDateTime m_startTime;
    QDateTime m_endTime;
    qreal m_count;
};

#endif // TASKDATA_H
