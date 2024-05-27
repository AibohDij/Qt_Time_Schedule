#include "taskwidget.h"
#include "task.h"

TaskWidget::TaskWidget(const TaskData &taskData, qreal height,QDate today,QWidget *parent)
    : QWidget(parent), m_taskData(taskData),m_today(today) {
    setupUi(taskData);
    setFixedHeight(height);
}

void TaskWidget::contextMenuEvent(QContextMenuEvent *event) {
    QMenu contextMenu(this);

    QAction *editAction = new QAction("详情", this);
    QAction *deleteAction = new QAction("删除", this);
    //链接信号和槽
    connect(editAction, &QAction::triggered, this, &TaskWidget::onEditTask);
    connect(deleteAction, &QAction::triggered, this, &TaskWidget::onDeleteTask);
    //菜单绑定
    contextMenu.addAction(editAction);
    contextMenu.addSeparator();
    contextMenu.addAction(deleteAction);
    //设置样式表
    contextMenu.setStyleSheet("background-color: white;");
    //执行
    contextMenu.exec(event->globalPos());
}

void TaskWidget::setupUi(const TaskData &taskData) {
    if (layout()) {
        delete layout();
    }
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *timeLabel;
    QLabel *nameLabel;
    if(taskData.type()==SingleTask){
        if(taskData.startTime().date()==taskData.endTime().date()){
            timeLabel = new QLabel(QString("时间段: %1 - %2")
                                               .arg(taskData.startTime().toString("HH:mm"))
                                           .arg(taskData.endTime().toString("HH:mm")), this);
        }
        else if(taskData.startTime().date()==m_today){
            timeLabel = new QLabel(QString("时间段: %1 - %2")
                                       .arg(taskData.startTime().toString("HH:mm"))
                                       .arg("24:00"), this);
        }
        else if(taskData.endTime().date()==m_today){
            timeLabel = new QLabel(QString("时间段: %1 - %2")
                                       .arg("00:00")
                                       .arg(taskData.endTime().toString("HH:mm")), this);
        }
        nameLabel = new QLabel(QString("任务名称: %1").arg(taskData.name()), this);

    }
    else if(taskData.type()==RepeatedTask){
        timeLabel = new QLabel(QString("时间段: %1 - %2")
                                   .arg(taskData.startTime().toString("HH:mm"))
                                   .arg(taskData.endTime().toString("HH:mm")), this);
        nameLabel = new QLabel(QString("任务名称: %1").arg(taskData.name()), this);
    }
    else{
        timeLabel = new QLabel(QString("截止时间: %1")
                                           .arg(taskData.endTime().toString("HH:mm")), this);
        nameLabel = new QLabel(QString("任务名称: %1").arg(taskData.name()), this);
    }
    layout->addWidget(nameLabel);
    layout->addWidget(timeLabel);
    setLayout(layout);
    QString bgColor = getPriorityColor(taskData.priority());
    setStyleSheet(QString("background-color: %1; border: 0px solid black;").arg(bgColor));
    adjustFontSizeToFit(timeLabel, nameLabel);
}

QString TaskWidget::getPriorityColor(Priority priority) {
    switch (priority) {
    case HighPriority:
        return "#FF6347";
    case MediumPriority:
        return "rgb(215, 185, 142)";
    case LowPriority:
        return "#9ACD32";
    default:
        return "rgba(200, 200, 255, 150)";
    }
}

void TaskWidget::adjustFontSizeToFit(QLabel *timeLabel, QLabel *nameLabel) {
    QFont font = timeLabel->font();
    font.setBold(true);
    QFontMetrics metrics(font);
    int maxHeight = height() / 2;
    while (metrics.height() > maxHeight) {
        font.setPointSize(font.pointSize() - 1);
        metrics = QFontMetrics(font);
    }
    timeLabel->setFont(font);
    nameLabel->setFont(font);
}

void TaskWidget::onEditTask() {
    qDebug() << "editTask" << m_taskData.name();
    Task editTaskUI;
    editTaskUI.setModifyMode(m_taskData);
    editTaskUI.setTaskData(m_taskData);
    editTaskUI.exec();
    m_taskData = editTaskUI.getData();
    emit editFinished(this);
}

void TaskWidget::onDeleteTask() {
    QMessageBox msgBox;
    msgBox.setInformativeText("确定要删除这个任务吗?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, "确认");
    msgBox.setButtonText(QMessageBox::No, "取消");
    msgBox.setDefaultButton(QMessageBox::No);

    int reply = msgBox.exec();

    if (reply == QMessageBox::Yes) {
        qDebug() << "deleteTask" << m_taskData.name();
        MyDataBase db;
        db.openDb();
        db.deleteTaskData(m_taskData);
        emit editFinished(this);
    } else {
        qDebug() << "取消删除任务" << m_taskData.name();
    }
}
