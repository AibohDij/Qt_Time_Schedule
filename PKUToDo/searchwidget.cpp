// searchwidget.cpp
#include "searchwidget.h"
#include <QHeaderView>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent) {
    setupUi();
}

void SearchWidget::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *searchLayout = new QHBoxLayout();

    QLabel *taskNameLabel = new QLabel("任务名称:", this);
    taskNameLabel->setObjectName("TaskNameLabel");
    taskNameEdit = new QLineEdit(this);
    taskNameEdit->setObjectName("TaskNameEdit");

    QLabel *startDateLabel = new QLabel("开始日期:", this);
    startDateLabel->setObjectName("StartDateLabel");
    startDateEdit = new QDateEdit(QDate::currentDate(), this);
    startDateEdit->setDisplayFormat("yyyy-MM-dd");
    startDateEdit->setCalendarPopup(true);
    startDateEdit->setObjectName("StartDateEdit");

    QLabel *endDateLabel = new QLabel("结束日期:", this);
    endDateLabel->setObjectName("EndDateLabel");
    endDateEdit = new QDateEdit(QDate::currentDate(), this);
    endDateEdit->setDisplayFormat("yyyy-MM-dd");
    endDateEdit->setCalendarPopup(true);
    endDateEdit->setObjectName("EndDateEdit");

    startDateEdit->setMinimumWidth(100);
    endDateEdit->setMinimumWidth(100);

    QLabel *priorityLabel = new QLabel("优先级:", this);
    priorityLabel->setObjectName("PriorityLabel");
    priorityComboBox = new QComboBox(this);
    priorityComboBox->setObjectName("PriorityComboBox");
    priorityComboBox->addItem("所有优先级");
    priorityComboBox->addItem("高优先级");
    priorityComboBox->addItem("中优先级");
    priorityComboBox->addItem("低优先级");

    searchButton = new QPushButton("搜索", this);
    connect(searchButton, &QPushButton::clicked, this, &SearchWidget::onSearchButtonClicked);


    newTaskButton = new QPushButton("新建",this);
    connect(newTaskButton, &QPushButton::clicked, this, &SearchWidget::onNewTaskButtonClicked);

    searchLayout->addWidget(taskNameLabel);
    searchLayout->addWidget(taskNameEdit);
    searchLayout->addWidget(startDateLabel);
    searchLayout->addWidget(startDateEdit);
    searchLayout->addWidget(endDateLabel);
    searchLayout->addWidget(endDateEdit);
    searchLayout->addWidget(priorityLabel);
    searchLayout->addWidget(priorityComboBox);
    searchLayout->addWidget(searchButton);
    searchLayout->addWidget(newTaskButton);

    resultsTable = new QTableWidget(this);
    resultsTable->setColumnCount(1);
    resultsTable->horizontalHeader()->hide();
    //resultsTable->verticalHeader()->hide();
    resultsTable->setShowGrid(false);
    resultsTable->setColumnWidth(0, 500);

    resultsTable->setStyleSheet("QTableWidget::item { border: 0.5px solid black; }");
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(resultsTable);
}

void SearchWidget::onSearchButtonClicked() {
    QString taskName = taskNameEdit->text();
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    int priority = priorityComboBox->currentIndex();
    qDebug()<<"priority"<<priority<<' '<<priorityComboBox->currentIndex();

    MyDataBase db;
    db.openDb();

    QString condition = "1=1";
    if (!taskName.isEmpty()) {
        condition += QString(" AND taskname LIKE '%%1%'").arg(taskName);
    }
    if (startDate.isValid()) {
        condition += QString(" AND DATE(start_time) >= '%1'").arg(startDate.toString("yyyy-MM-dd"));
    }
    if (endDate.isValid()) {
        condition += QString(" AND DATE(end_time) <= '%1'").arg(endDate.toString("yyyy-MM-dd"));
    }
    if (priorityComboBox->currentIndex() != 0) {
        condition += QString(" AND priority = %1-1").arg(priority);
    }
    qDebug()<<condition;
    QList<TaskData> tasks = db.findTaskData(condition);
    displayResults(tasks);
}


void SearchWidget::onNewTaskButtonClicked()
{
    qDebug() << "addTask in searching";
    Task addTaskUI;
    addTaskUI.exec();
    TaskData new_taskData = addTaskUI.getData();
    MyDataBase db;db.openDb();
    db.insertTaskData(new_taskData);
    QString taskName = new_taskData.name();
    qDebug() << "New task added: " << taskName;
    onSearchButtonClicked();
}



bool comparePriority(const TaskData &task1, const TaskData &task2) {
    return task1.priority() < task2.priority(); // 按照优先级升序排序
}
void SearchWidget::displayResults(const QList<TaskData> &tasks) {
    resultsTable->setRowCount(tasks.size());
    QList<TaskData> sortedTasks = tasks; // 复制一份 tasks 列表以免修改原始数据
    std::sort(sortedTasks.begin(), sortedTasks.end(), comparePriority);
    for (int row = 0; row < tasks.size(); ++row) {
        SearchResultWidget *taskWidget = new SearchResultWidget(sortedTasks[row], this);
        connect(taskWidget,&SearchResultWidget::editFinished,this,&SearchWidget::onSearchButtonClicked);
        resultsTable->setCellWidget(row, 0, taskWidget);
        resultsTable->setRowHeight(row,50);
    }
}

SearchResultWidget::SearchResultWidget(const TaskData &taskData, QWidget *parent)
    : QWidget(parent), m_taskData(taskData),timer(nullptr) {
    setupUi();
}

TaskData SearchResultWidget::taskData()
{
    return m_taskData;
}

void SearchResultWidget::setAlarm()
{
    if (m_taskData.type() == SingleTask)
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        qreal sec = currentTime.secsTo(m_taskData.startTime()) - 60;
        if(sec>=0)
        {
            timer = new QTimer();
            timer->start(sec * 1000);
            timer->setSingleShot(true);
        }
    }
    else if(m_taskData.type() == RepeatedTask)
    {
        QDateTime currentTime = QDateTime::currentDateTime();
        QDateTime finalStartTime;
        finalStartTime.setDate(m_taskData.endTime().date());
        finalStartTime.setTime(m_taskData.startTime().time());
        qreal sec = currentTime.secsTo(finalStartTime);
        if(sec>=0)
        {
            QString week = currentTime.toString("ddd");
            int num_week;
            if(week=="星期一")
                num_week=0;
            else if(week=="星期二")
                num_week=1;
            else if(week=="星期三")
                num_week=2;
            else if(week=="星期四")
                num_week=3;
            else if(week=="星期五")
                num_week=4;
            else if(week=="星期六")
                num_week=5;
            else
                num_week=6;
            for(int i=0;;++i)
            {
                if(m_taskData.getRepeatDays()[(i+num_week)%7]==0)
                    continue;
                finalStartTime.setDate(currentTime.date().addDays(i));
                sec = currentTime.secsTo(finalStartTime);
                if(sec<60)
                    continue;
                timer = new QTimer();
                timer->start(sec*1000);
                timer->setSingleShot(true);
                break;
            }
        }
    }

}

void SearchResultWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu contextMenu(this);
    QAction *editAction = new QAction("详情",this);
    QAction *deleteAction = new QAction("删除",this);
    connect(editAction,&QAction::triggered,this,&SearchResultWidget::onEdit);
    connect(deleteAction,&QAction::triggered,this,&SearchResultWidget::onDelete);
    contextMenu.addAction(editAction);
    contextMenu.addSeparator();
    contextMenu.addAction(deleteAction);

    contextMenu.setStyleSheet("background-color: white;");

    contextMenu.exec(event->globalPos());
}


void SearchResultWidget::setupUi() {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10); // 设置布局的外边距

    QLabel *timeLabel = nullptr;
    QLabel *nameLabel = nullptr;

    if (m_taskData.type() == SingleTask) {
        /*if (m_taskData.startTime().date() == m_taskData.endTime().date()) {
            timeLabel = new QLabel(QString("%1 - %2 ")
                                       .arg(m_taskData.startTime().toString("yyyy-MM-dd HH:mm"))
                                       .arg(m_taskData.endTime().toString("yyyy-MM-dd HH:mm")));
        }*/
        timeLabel = new QLabel(QString("%1 - %2 ")
                                   .arg(m_taskData.startTime().toString("yyyy-MM-dd HH:mm"))
                                   .arg(m_taskData.endTime().toString("yyyy-MM-dd HH:mm")));
        nameLabel = new QLabel(QString("计划: %1").arg(m_taskData.name()), this);
    } else if (m_taskData.type() == RepeatedTask) {
        timeLabel = new QLabel(QString("时间段: %1 - %2  具体日期请看详情")
                                   .arg(m_taskData.startTime().toString("HH:mm"))
                                   .arg(m_taskData.endTime().toString("HH:mm")), this);
        nameLabel = new QLabel(QString("计划: %1").arg(m_taskData.name()), this);
    } else {
        timeLabel = new QLabel(QString("截止时间:%2 %1 ")
                                   .arg(m_taskData.endTime().toString("HH:mm"))
                                   .arg(m_taskData.endTime().toString("yyyy-MM-dd")), this);
        nameLabel = new QLabel(QString("计划: %1").arg(m_taskData.name()), this);
    }

    timeLabel->setObjectName("timeLabel_search");
    nameLabel->setObjectName("nameLabel_search");
    // 设置最小宽度
    timeLabel->setMinimumWidth(180);
    nameLabel->setMinimumWidth(150);

    QString labelStyleSheet = "border: 1px solid black;"
                              "border-radius: 15px;"
                              "padding: 5px;"
                              "font-family: 'STFangsong';"
                              "font-weight:bold;"
                              "color: black;"
                              "font-size: 11pt;";
    nameLabel->setStyleSheet(labelStyleSheet);
    timeLabel->setStyleSheet(labelStyleSheet);

    layout->addWidget(nameLabel);
    layout->addWidget(timeLabel);

    // 添加占位符，使得布局宽度更大
    layout->addStretch(1);
    setLayout(layout);

    setPriorityColor(m_taskData.priority());

    // QFile file(":/styles/styles/testStyle.qss");
    // if (file.open(QFile::ReadOnly | QFile::Text)) {
    //     QTextStream stream(&file);
    //     QString styleSheet = stream.readAll();
    //     this->setStyleSheet(styleSheet);
    // }

    // // 获取背景颜色，并确保优先级高于 QSS 文件中的样式
    // QString bgColor = getPriorityColor(m_taskData.priority());
    // setStyleSheet(this->styleSheet() + QString("QLabel#timeLabel_search,QLabel#nameLabel_search { background-color: %1; }").arg(bgColor));


}

QString SearchResultWidget::getPriorityColor(Priority priority) {
    switch (priority) {
    case HighPriority:
        return "rgba(255, 0, 0, 150)";
    case MediumPriority:
        return "rgba(255, 255, 0, 150)";
    case LowPriority:
        return "#9ACD32";
    default:
        return "rgba(200, 200, 255, 150)";
    }
}

QString SearchResultWidget::priorityToString(Priority priority) {
    switch (priority) {
    case HighPriority:
        return "高";
    case MediumPriority:
        return "中";
    case LowPriority:
        return "低";
    default:
        return "未知";
    }
}

void SearchResultWidget::setPriorityColor(Priority priority)
{
    switch (priority) {
    case LowPriority:
        setStyleSheet("background-color: #9ACD32;"); // 绿色
        break;
    case MediumPriority:
        setStyleSheet("background-color: rgb(215, 185, 142);"); // 黄色
        break;
    case HighPriority:
        setStyleSheet("background-color: #FF6347;"); // 红色
        break;
    }
}

void SearchResultWidget::onEdit()
{
    qDebug() << "Edit requested on searching:" << m_taskData.name();
    Task editTaskUI;
    editTaskUI.setModifyMode(m_taskData);
    editTaskUI.setTaskData(m_taskData);
    editTaskUI.exec();
    if(timer != nullptr)
        timer->stop();
    m_taskData = editTaskUI.getData();
    emit editFinished();
}

void SearchResultWidget::onDelete()
{
    qDebug() << "Delete requested on searching:" << m_taskData.name();
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
        if(timer != nullptr)
            timer->stop();
        emit editFinished();
    } else {
        qDebug() << "取消删除任务" << m_taskData.name();
    }
}


TodayTasksWidget::TodayTasksWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
    displayTodayTasks();
}

void TodayTasksWidget::TodayUpdate()
{
    displayTodayTasks();
}

void TodayTasksWidget::newTask()
{
    qDebug() << "addTask in today";
    Task addTaskUI;
    addTaskUI.exec();
    TaskData new_taskData = addTaskUI.getData();
    MyDataBase db;db.openDb();
    db.insertTaskData(new_taskData);
    QString taskName = new_taskData.name();
    qDebug() << "New task added: " << taskName;
    TodayUpdate();
}

void TodayTasksWidget::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QLabel *titleLabel = new QLabel("今日计划", this);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");

    QPushButton* renewButton = new QPushButton("更新",this);
    renewButton->setMaximumWidth(200);
    connect(renewButton,&QPushButton::clicked,this,&TodayTasksWidget::TodayUpdate);

    QPushButton* newButton = new QPushButton("新建",this);
    newButton->setMaximumWidth(200);
    connect(newButton,&QPushButton::clicked,this,&TodayTasksWidget::newTask);
    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(newButton);
    buttonLayout->addWidget(renewButton);


    tasksTable = new QTableWidget(this);
    tasksTable->setColumnCount(1);
    tasksTable->horizontalHeader()->hide();
    //tasksTable->verticalHeader()->hide();
    tasksTable->setColumnWidth(0, 480);
    tasksTable->setShowGrid(false);
    tasksTable->setStyleSheet("QTableWidget::item { border: 0.5px solid black; }");

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tasksTable);

    setLayout(mainLayout);

    trayIcon = new QSystemTrayIcon();
    trayIcon->setIcon(QIcon(":/icons/widgets_icons/check-sign-in-a-rounded-black-square.png"));
    trayIcon->setToolTip(QString("PKUToDo"));
    trayIcon->show();
}

bool compareStartTime(const TaskData &task1, const TaskData &task2) {
    if(task1.type()==DeadlineTask){
        return task1.endTime() < task2.endTime();;
    }
    if(task2.type()==DeadlineTask){
        return task1.endTime() < task2.endTime();;
    }

    return task1.startTime() < task2.startTime();
}

void TodayTasksWidget::displayTodayTasks()
{
    MyDataBase db;
    db.openDb();
    QDate today = QDate::currentDate();
    QList<TaskData> todayTasks = db.findTaskDataByDate(today);
    QList<TaskData> sortedTasks = todayTasks; // 复制一份 tasks 列表以免修改原始数据
    std::sort(sortedTasks.begin(), sortedTasks.end(), comparePriority);
    tasksTable->clear();
    tasksTable->setRowCount(todayTasks.size());
    for (int row = 0; row < todayTasks.size(); ++row) {
        SearchResultWidget *taskWidget = new SearchResultWidget(sortedTasks[row], this);
        taskWidget->setAlarm();
        if(taskWidget->timer!=nullptr)
        {
            qDebug()<<"Signal Formed.";
            connect(taskWidget->timer,&QTimer::timeout,this,[name = taskWidget->taskData().name(),this](){this->trayIcon->showMessage("提醒", name+QString("计划事项即将开始"));});
        }
        connect(taskWidget,&SearchResultWidget::editFinished,this,&TodayTasksWidget::TodayUpdate);
        tasksTable->setCellWidget(row, 0, taskWidget);
        tasksTable->setRowHeight(row, 50);
    }
}

/*void TodayTasksWidget::presentNotice(const QString &name)
{
    trayIcon->showMessage("提醒", name);
    qDebug()<<"Showed.";
}*/

ToDoWidget::ToDoWidget(const ToDoData &toDoData, QWidget *parent) :
    QWidget(parent),m_data(toDoData) {
    nameLabel = new QLabel(QString("待办： %1").arg(toDoData.name()), this);
    QString labelStyleSheet = "border: 1px solid black;"
                              "border-radius: 15px;"
                              "padding: 5px;"
                              "font-family: 'STFangsong';"
                              "font-weight:bold;"
                              "color: black;"
                              "font-size: 11pt;";
    nameLabel->setStyleSheet(labelStyleSheet);


    if (toDoData.isDone()) {
        nameLabel->setStyleSheet(labelStyleSheet+QString("text-decoration: line-through;"));
        isDone = true;
    }
    int totalSeconds = toDoData.expectTime();
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600)/60;
    expectTimeLabel = new QLabel(QString("预计：%1小时 %2分钟").arg(hours).arg(minutes), this); // 按小时和分钟显示
    expectTimeLabel->setStyleSheet(labelStyleSheet);
    startButton = new QPushButton("开始", this);
    //startButton->setStyleSheet("background-color: white;");
    connect(startButton,&QPushButton::clicked,this,&ToDoWidget::on_startButton_clicked);
    // 设置布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(expectTimeLabel);
    layout->addWidget(startButton);


    // 根据优先级设置背景颜色
    setPriorityColor(toDoData.priority());

    setLayout(layout);
}

void ToDoWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu contextMenu(this);
    QAction *editAction = new QAction("详情",this);
    QAction *deleteAction = new QAction("删除",this);
    connect(editAction,&QAction::triggered,this,&ToDoWidget::onEdit);
    connect(deleteAction,&QAction::triggered,this,&ToDoWidget::onDelete);

    contextMenu.addAction(editAction);
    contextMenu.addSeparator();
    contextMenu.addAction(deleteAction);
    if(isDone){
        QAction *renewAction = new QAction("恢复",this);
        connect(renewAction,&QAction::triggered,this,&ToDoWidget::onRenew);
        contextMenu.addSeparator();
        contextMenu.addAction(renewAction);
    }
    contextMenu.setStyleSheet("background-color: white;");

    contextMenu.exec(event->globalPos());
}

void ToDoWidget::setPriorityColor(Priority priority) {
    switch (priority) {
    case LowPriority:
        setStyleSheet("background-color: #9ACD32;"); // 绿色
        break;
    case MediumPriority:
        setStyleSheet("background-color: rgb(215, 185, 142);"); // 黄色
        break;
    case HighPriority:
        setStyleSheet("background-color: #FF6347;"); // 红色
        break;
    }
}
QString getRandomBackground(){
    QString imagePath = ":/background/background";

    // 获取图片文件夹中所有文件
    QDir directory(imagePath);
    QFileInfoList fileList = directory.entryInfoList(QDir::Files);

    // 如果文件列表为空，无法选择图片
    if (fileList.isEmpty()) {
        qDebug() << "No images found in the specified directory.";
        return "";
    }

    // 生成一个随机索引以选择图片
    int randomIndex = QRandomGenerator::global()->bounded(0, fileList.size());

    // 选择随机图片文件
    QString randomImagePath = fileList[randomIndex].absoluteFilePath();
    return randomImagePath;
}

void ToDoWidget::on_startButton_clicked()
{
    if(m_data.isDone()){
        QMessageBox msgBox;
        msgBox.setInformativeText("该待办已完成，请右键删除或恢复为未完成");
        msgBox.exec();
        return;
    }


    CountdownWidget *countdownWidget = new CountdownWidget(m_data);
    countdownWidget->setWindowModality(Qt::ApplicationModal);
    QIcon windowIcon(":/icons/widgets_icons/wristwatch.png");
    countdownWidget->setWindowIcon(windowIcon);
    countdownWidget->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    QPalette PAllbackground = this->palette();
    //QImage ImgAllbackground(":/background/background/background_canoe.png");
    QImage ImgAllbackground(getRandomBackground());
    qDebug()<<getRandomBackground();
    QImage fitimgpic=ImgAllbackground.scaled(countdownWidget->width(),countdownWidget->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    countdownWidget->setPalette(PAllbackground);

    countdownWidget->show();
    connect(countdownWidget,&CountdownWidget::completed,this,&ToDoWidget::setComplete);
}

void ToDoWidget::onEdit()
{
    qDebug()<<"ToDo edit is called";
    ToDoEditDialog tmpEditor;
    tmpEditor.setToDoData(m_data);
    tmpEditor.exec();
    m_data = tmpEditor.generateToDo();
    emit editFinished();
}

void ToDoWidget::onDelete()
{
    qDebug()<<"ToDo delete is called";
    QMessageBox msgBox;
    msgBox.setInformativeText("确定要删除这个待办吗?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, "确认");
    msgBox.setButtonText(QMessageBox::No, "取消");
    msgBox.setDefaultButton(QMessageBox::No);

    int reply = msgBox.exec();

    if (reply == QMessageBox::Yes) {
        qDebug() << "deleteToDo" << m_data.name();
        MyDataBase db;
        db.openDb();
        db.deleteToDoData(m_data);
        emit editFinished();
    } else {
        qDebug() << "取消删除待办" << m_data.name();
    }
}

void ToDoWidget::onRenew()
{
    qDebug()<<"ToDo renew is called";
    ToDoData newdata = m_data;
    newdata.setIsDone(false);
    MyDataBase db;
    db.openDb();
    db.modifyToDoData(m_data,newdata);
    m_data.setIsDone(false);
    emit editFinished();
}

void ToDoWidget::setComplete()
{
    qDebug()<<"ToDo complete is called";
    ToDoData newdata = m_data;
    newdata.setIsDone(true);
    MyDataBase db;
    db.openDb();
    db.modifyToDoData(m_data,newdata);
    m_data.setIsDone(true);
    emit editFinished();
}

ToDoView::ToDoView(QWidget *parent) :
    QWidget(parent), m_db(nullptr) {

    QLabel *titleLabel = new QLabel("待办集", this);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");


    addButton = new QPushButton("添加待办", this);
    tableWidget = new QTableWidget(this);

    addButton->setMaximumWidth(200);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(addButton);
    layout->addWidget(tableWidget);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &ToDoView::onAddButtonClicked);
    refreshToDoList();
}

void ToDoView::setDatabase(MyDataBase *db) {
    m_db = db;
    refreshToDoList();
}

void ToDoView::onAddButtonClicked() {
    ToDoEditDialog dialog(this);
    dialog.setDatabase(m_db);
    if (dialog.exec() == QDialog::Accepted) {
        refreshToDoList();
    }
}

void ToDoView::refreshToDoList() {
    MyDataBase db;db.openDb();

    QList<ToDoData> toDoList = db.findToDoData("1=1"); // 查询所有 ToDo 项
    std::sort(toDoList.begin(), toDoList.end(), [](const ToDoData &a, const ToDoData &b) {
        if (a.isDone() != b.isDone())
            return !a.isDone();
        return a.priority() < b.priority();
    });

    tableWidget->clear();
    tableWidget->setRowCount(toDoList.size());
    tableWidget->setColumnCount(1);
    tableWidget->setColumnWidth(1,400);
    tableWidget->horizontalHeader()->hide();
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    qDebug()<<"toDoList Size"<<toDoList.size();
    for (int i = 0; i < toDoList.size(); ++i) {
        ToDoWidget *widget = new ToDoWidget(toDoList.at(i));
        connect(widget,&ToDoWidget::editFinished,this,&ToDoView::refreshToDoList);
        tableWidget->setCellWidget(i, 0, widget);
        tableWidget->setRowHeight(i,50);
    }

}

void ToDoView::populateTable() {
    //初始化列表
}
