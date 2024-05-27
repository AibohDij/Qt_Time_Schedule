#include "timeaxis.h"
#include <QDebug>
#include <QIcon>
TimeAxis::TimeAxis(int windowWidth, int windowHeight, qreal stride, QDate date, QWidget *parent)
    : QGraphicsView(parent), windowWidth(windowWidth), windowHeight(windowHeight), stride(stride), today(date) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(windowWidth, windowHeight);
    setupTimeAxis();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void TimeAxis::setupTimeAxis() {
    QString dateText = today.toString("yyyy-MM-dd");
    dateTextItem = scene->addText(dateText);
    if(theme=="black"){
        dateTextItem->setDefaultTextColor(Qt::white);
    }
    else{
        dateTextItem->setDefaultTextColor(Qt::black);
    }
    QFont font = dateTextItem->font();
    font.setPointSize(14); // Adjust size as needed
    font.setBold(true);
    dateTextItem->setFont(font);

    QRectF textRect = dateTextItem->boundingRect();
    dateTextItem->setPos((windowWidth - textRect.width()*2) / 2, -textRect.height() - 10);

    for (int hour = 0; hour <= 24; ++hour) {
        qreal y = hour * stride;
        QGraphicsLineItem *line = new QGraphicsLineItem(-4, y, windowWidth - 50, y);
        if(theme=="black"){
            QPen pen(Qt::white);
            line->setPen(pen);
        }
        scene->addItem(line);
        if (hour != 24) {
            QGraphicsLineItem *dashedLine = new QGraphicsLineItem(0, y + stride / 2, windowWidth - 70, y + stride / 2);
            QPen pen(Qt::black);
            pen.setStyle(Qt::DashLine);
            if(theme=="black"){
                pen.setColor(QColor(255,255,255));
            }
            dashedLine->setPen(pen);
            scene->addItem(dashedLine);
        }
        QString hourText;
        hourText = QString("%1:00").arg(hour, 2, 10, QChar('0'));
        QGraphicsTextItem *textItem = scene->addText(hourText);
        if(theme=="black"){
            textItem->setDefaultTextColor(Qt::white);
        }
        else{
            textItem->setDefaultTextColor(Qt::black);
        }
        qreal textWidth = textItem->boundingRect().width();
        textItem->setPos(-textWidth - 5, y - 10);
    }

}

void TimeAxis::updateTimeAxis(TaskWidget* widget) {
    scene->removeItem(widget->graphicsProxyWidget());
    widget->deleteLater();
    resetScene();
}

// void TimeAxis::addTaskWidget(const TaskData &taskData) {
//     qDebug()<<"addTask is called";
//     qreal startY = taskData.startTime().time().hour() * stride +
//                    taskData.startTime().time().minute() * stride / 60;
//     qreal endY = taskData.endTime().time().hour() * stride +
//                  taskData.endTime().time().minute() * stride / 60;
//     qreal height = endY - startY;
//     TaskWidget *taskWidget = new TaskWidget(taskData, height);
//     connect(taskWidget, &TaskWidget::editFinished, this, &TimeAxis::updateTimeAxis);
//     QGraphicsProxyWidget *proxy = scene->addWidget(taskWidget);
//     proxy->setPos(0, startY);
// }
TaskWidget * TimeAxis::addTaskWidget(const TaskData &taskData) {
    //qDebug() << "addTaskWidget is called";
    qreal startY = 0.0 , endY = 0.0;
    if(taskData.type()==SingleTask)
    {
        if(taskData.startTime().date()==taskData.endTime().date()){
            startY = taskData.startTime().time().hour() * stride +
                           taskData.startTime().time().minute() * stride / 60;
            endY = taskData.endTime().time().hour() * stride +
                         taskData.endTime().time().minute() * stride / 60;
        }
        else if(taskData.startTime().date()==today){
            startY = taskData.startTime().time().hour() * stride +
                     taskData.startTime().time().minute() * stride / 60;
            endY =24 * stride ;
        }
        else if(taskData.endTime().date()==today){
            startY = 0;
            endY = taskData.endTime().time().hour() * stride +
                   taskData.endTime().time().minute() * stride / 60;
        }
    }
    else if(taskData.type()==RepeatedTask){
        startY = taskData.startTime().time().hour() * stride +
                 taskData.startTime().time().minute() * stride / 60;
        endY = taskData.endTime().time().hour() * stride +
               taskData.endTime().time().minute() * stride / 60;
    }
    else{

        endY = taskData.endTime().time().hour() * stride +
               taskData.endTime().time().minute() * stride / 60;
        startY = endY-2*stride;
    }
    qreal height = endY - startY;

    qreal startX = 0;
    qreal taskWidth = 150;

    while (true) {
        bool overlap = false;
        for (QGraphicsItem *item : scene->items()) {
            if (QGraphicsProxyWidget *proxy = dynamic_cast<QGraphicsProxyWidget *>(item)) {
                if (TaskWidget *existingTaskWidget = dynamic_cast<TaskWidget *>(proxy->widget())) {
                    QRectF existingRect = proxy->sceneBoundingRect();
                    if (existingRect.intersects(QRectF(startX, startY, taskWidth, height))) {
                        overlap = true;
                        startX = existingRect.right() + 5;
                        break;
                    }
                }
            }
        }
        if (!overlap) {
            break;
        }
    }

    TaskWidget *taskWidget = new TaskWidget(taskData, std::max(height,35.0),today);
    connect(taskWidget, &TaskWidget::editFinished, this, &TimeAxis::updateTimeAxis);
    //connect(taskWidget, &TaskWidget::deleteRequested, this, &TimeAxis::deleteTaskWidget);
    QGraphicsProxyWidget *proxy = scene->addWidget(taskWidget);
    proxy->setPos(startX, startY);
    return taskWidget;
}



void TimeAxis::drawDayTasks() {
    resetScene();
}

void TimeAxis::resetScene() {
    scene->clear();
    setupTimeAxis();
    MyDataBase db;
    db.openDb();
    QList<TaskData> todayTasks = db.findTaskDataByDate(today);
    for (const TaskData &task : todayTasks) {
        addTaskWidget(task);
    }
}

void TimeAxis::contextMenuEvent(QContextMenuEvent *event) {
    QGraphicsItem *item = itemAt(event->pos());
    if (item) {
        // 检查 item 是否为 QGraphicsProxyWidget
        QGraphicsProxyWidget *proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(item);
        if (proxyWidget) {
            QWidget *widget = proxyWidget->widget();
            TaskWidget *taskWidget = dynamic_cast<TaskWidget*>(widget);
            if (taskWidget) {
                // 创建 TaskWidget 的上下文菜单
                taskWidget->contextMenuEvent(event);
                return;
            }
        }
    }

    // 如果没有点击到 TaskWidget，则显示 TimeAxis 的上下文菜单
    QMenu contextMenu(this);

    QAction *addnewAction = new QAction("新建", this);

    // 链接信号和槽
    connect(addnewAction, &QAction::triggered, this, &TimeAxis::addnewTask);
    // 菜单绑定
    contextMenu.addAction(addnewAction);
    // 设置样式表
    contextMenu.setStyleSheet("background-color: white;");
    // 执行
    contextMenu.exec(event->globalPos());
}

void TimeAxis::addnewTask(){
    qDebug() << "addTask";
    Task addTaskUI;
    addTaskUI.exec();
    TaskData new_taskData = addTaskUI.getData();
    TaskWidget *newTask = addTaskWidget(new_taskData);
    MyDataBase db;db.openDb();
    db.insertTaskData(new_taskData);
    QString taskName = new_taskData.name();
    qDebug() << "New task added: " << taskName;
    updateTimeAxis(newTask);
}


TimeAxisWindow::TimeAxisWindow(QDate selectedDate, QWidget *parent)
    : QMainWindow(parent)
{
    int windowWidth = 800;
    int windowHeight = 800;
    qreal stride = 48.0;

    // 创建 TimeAxis 对象并设置日期
    timeAxis = new TimeAxis(windowWidth, windowHeight, stride, selectedDate);
    timeAxis->drawDayTasks();

    // 将 TimeAxis 对象设置为窗口的中心部件
    setCentralWidget(timeAxis);
}

void TimeAxisWindow::setTheme(QString t)
{
    theme=t;
    timeAxis->theme=t;

}
