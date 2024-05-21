#include "task.h"
#include "ui_task.h"

Task::Task(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Task)
{
    ui->setupUi(this);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->dateEdit_start_repeat->setDate(currentDateTime.date());
    ui->dateEdit_end_repeat->setDate(currentDateTime.date());
    ui->dateTimeEdit_start_once->setDateTime(currentDateTime);
    ui->dateTimeEdit_end_once->setDateTime(currentDateTime);
    ui->dateTimeEdit_deadline->setDateTime(currentDateTime);
    connect(ui->radioButton_Once, &QRadioButton::toggled, this, &Task::TimeSetting);
    connect(ui->radioButton_Repeat, &QRadioButton::toggled, this, &Task::TimeSetting);
    connect(ui->radioButton_Deadline, &QRadioButton::toggled, this, &Task::TimeSetting);
    //设置日期按钮的互斥事件
    connect(ui->checkBox_everyDay, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_everyDay->isChecked()) {
            ui->checkBox_Monday->setChecked(false);
            ui->checkBox_TuesDay->setChecked(false);
            ui->checkBox_Wednesday->setChecked(false);
            ui->checkBox_Thursday->setChecked(false);
            ui->checkBox_Friday->setChecked(false);
            ui->checkBox_Saturday->setChecked(false);
            ui->checkBox_Sunday->setChecked(false);
        }
    });

    connect(ui->checkBox_Monday, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_Monday->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });

    connect(ui->checkBox_TuesDay, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_TuesDay->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });

    connect(ui->checkBox_Wednesday, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_Wednesday->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });

    connect(ui->checkBox_Thursday, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_Thursday->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });

    connect(ui->checkBox_Friday, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_Friday->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });

    connect(ui->checkBox_Saturday, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_Saturday->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });

    connect(ui->checkBox_Sunday, &QCheckBox::clicked, this, [=]() {
        if (ui->checkBox_Sunday->isChecked()) {
            ui->checkBox_everyDay->setChecked(false);
        }
    });


}

Task::~Task()
{
    delete ui;
}

void Task::setTaskData(const TaskData &data)
{
    //设置时间
    QDateTime currentDateTime_Start =data.startTime();
    QDateTime currentDateTime_End =data.endTime();
    ui->dateEdit_start_repeat->setDate(currentDateTime_Start.date());
    ui->dateEdit_end_repeat->setDate(currentDateTime_End.date());
    ui->dateTimeEdit_start_once->setDateTime(currentDateTime_Start);
    ui->dateTimeEdit_end_once->setDateTime(currentDateTime_End);
    ui->dateTimeEdit_deadline->setDateTime(currentDateTime_End);
    ui->timeEdit_start_repeat->setTime(currentDateTime_Start.time());
    ui->timeEdit_end_repeat->setTime(currentDateTime_End.time());
    ui->plainTextEdit_Name->setPlainText(data.name());
    ui->plainTextEdit_Details->setPlainText(data.detail());
    //优先级
    switch(data.priority()){
        case HighPriority:{
            ui->radioButton_high->setChecked(1);
            break;
        }
        case MediumPriority:{
            ui->radioButton_medium->setChecked(1);
            break;
        }
        case LowPriority:{
            ui->radioButton_low->setChecked(1);
            break;
        }
    }
    //类型
    switch(data.type()){
        case SingleTask:{
            ui->radioButton_Once->setChecked(1);
            ui->stackedWidget_types->setCurrentIndex(SingleTask);
            break;

        }
        case RepeatedTask:{
            ui->radioButton_Repeat->setChecked(1);
            ui->stackedWidget_types->setCurrentIndex(RepeatedTask);
            if(data.repeatDaysToInt()==127){
                ui->checkBox_everyDay->setChecked(1);
            }
            else{
                ui->checkBox_Monday->setChecked(data.getRepeatDays()[0]);
                ui->checkBox_TuesDay->setChecked(data.getRepeatDays()[1]);
                ui->checkBox_Wednesday->setChecked(data.getRepeatDays()[2]);
                ui->checkBox_Thursday->setChecked(data.getRepeatDays()[3]);
                ui->checkBox_Friday->setChecked(data.getRepeatDays()[4]);
                ui->checkBox_Saturday->setChecked(data.getRepeatDays()[5]);
                ui->checkBox_Sunday->setChecked(data.getRepeatDays()[6]);
            }
            break;
        }
        case DeadlineTask:{
            ui->radioButton_Deadline->setChecked(1);
            ui->stackedWidget_types->setCurrentIndex(DeadlineTask);
            break;
        }
    }

}

// !记得加入错误提示!
TaskData Task::generatetask()
{
    // 设置任务名称和详细描述
    QString name = ui-> plainTextEdit_Name-> toPlainText();
    QString detail = ui-> plainTextEdit_Details-> toPlainText();
    // 设置任务状态
    bool is_done = false;
    bool overdue = false;
    // 设置优先级和任务类型
    Priority priority = LowPriority;
    TaskType newtype = type;
    if(ui->radioButton_high->isChecked()){
        priority = HighPriority;

    }
    else if(ui->radioButton_medium->isChecked()){
        priority = MediumPriority;
    }
    else if(ui->radioButton_low->isChecked()){
        priority = LowPriority;
    }

    QDateTime startTime = QDateTime::currentDateTime();
    QDateTime endTime = QDateTime::currentDateTime().addSecs(3600); // 结束时间设置为当前时间后1h
    // 设置重复日数组 (例如：每周一、周三和周五) 初始化
    std::array<bool, 7> repeatDays = {false,false,false,false,false,false,false};
    switch(type){
        case SingleTask:{
            startTime = ui -> dateTimeEdit_start_once->dateTime();
            endTime = ui ->dateTimeEdit_end_once->dateTime();
            qDebug() << "Start Time:" << startTime;
            qDebug() << "End Time:" << endTime;
            break;
        }
        case RepeatedTask:{
            startTime.setDate(ui ->dateEdit_start_repeat->date());
            startTime.setTime(ui ->timeEdit_start_repeat->time());
            endTime.setDate(ui ->dateEdit_end_repeat->date());
            endTime.setTime(ui ->timeEdit_end_repeat->time());
            if(!ui->checkBox_everyDay->isChecked())
            {
                repeatDays[0] = ui->checkBox_Monday->isChecked();
                repeatDays[1] = ui->checkBox_TuesDay->isChecked();
                repeatDays[2] = ui->checkBox_Wednesday->isChecked();
                repeatDays[3] = ui->checkBox_Thursday->isChecked();
                repeatDays[4] = ui->checkBox_Friday->isChecked();
                repeatDays[5] = ui->checkBox_Saturday->isChecked();
                repeatDays[6] = ui->checkBox_Sunday->isChecked();
            }
            else{
                std::fill(repeatDays.begin(), repeatDays.end(), true);
            }
            break;
        }
        case DeadlineTask:{
            endTime = ui->dateTimeEdit_deadline->dateTime();
            break;
        }
    }
    // 创建任务对象并初始化所有属性
    TaskData task(startTime, endTime, name, detail, priority, newtype, is_done, overdue, repeatDays);

    return task;
}

void Task::on_pushButton_accept_clicked()
{
    MyDataBase db;
    db.openDb();
    TaskData newTask = generatetask();
    //错误校验
    if (newTask.name().isEmpty()) {
        QMessageBox::warning(this, "错误", "任务名称不能为空！");
        return;
    }
    if (newTask.startTime() >= newTask.endTime()) {
        QMessageBox::warning(this, "错误", "任务的开始时间必须早于结束时间！");
        return;
    }
    if (newTask.type()==SingleTask&&newTask.startTime().secsTo(newTask.endTime()) > 24 * 3600) {
        QMessageBox::warning(this, "错误", "单次任务的持续时间不建议超过24小时！");
        return;
    }
    if(!isModifyMode){
        db.insertTaskData(newTask);
    }
    else{
        db.modifyTaskData(originData,newTask);
        originData=newTask;
    }
    db.queryTaskData();
    this->accept();
}



void Task::on_pushButton_cancel_clicked()
{
    this->close();
}

void Task::setModifyMode(const TaskData &originTask)
{
    isModifyMode=true;
    this->originData=originTask;
}

TaskData Task::getData()
{
    return originData;
}

void Task::TimeSetting()
{

    if(ui->radioButton_Once->isChecked()){
        ui->stackedWidget_types->setCurrentIndex(0);
        type = SingleTask;
    }
    else if(ui->radioButton_Repeat->isChecked()){
        ui->stackedWidget_types->setCurrentIndex(1);
        type = RepeatedTask;
    }
    else if(ui->radioButton_Deadline->isChecked()){
        ui->stackedWidget_types->setCurrentIndex(2);
        type = DeadlineTask;
    }
}

