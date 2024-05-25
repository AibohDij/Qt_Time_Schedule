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
            //qDebug() << "Start Time:" << startTime;
            //qDebug() << "End Time:" << endTime;
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
            startTime = ui->dateTimeEdit_deadline->dateTime().addSecs(-3600);
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




ToDoEditDialog::ToDoEditDialog(QWidget *parent) :
    QDialog(parent),
    m_db(nullptr),
    m_isEditMode(false)
{
    // 创建界面控件
    nameLineEdit = new QLineEdit(this);
    hoursSpinBox = new QSpinBox(this);
    minutesSpinBox = new QSpinBox(this);
    priorityComboBox = new QComboBox(this);
    isDoneCheckBox = new QCheckBox(this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");

    // 配置控件
    hoursSpinBox->setRange(0, 23); // 小时范围：0 到 23
    minutesSpinBox->setRange(0, 59); // 分钟范围：0 到 59

    priorityComboBox->addItem("低", LowPriority);
    priorityComboBox->addItem("中", MediumPriority);
    priorityComboBox->addItem("高", HighPriority);

    isDoneCheckBox->setChecked(false); // 默认未完成

    // 布局
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("代办事项:", nameLineEdit);
    formLayout->addRow("预期时间（小时）:", hoursSpinBox);
    formLayout->addRow("预期时间（分钟）:", minutesSpinBox);
    formLayout->addRow("优先级:", priorityComboBox);
    formLayout->addRow("已完成:", isDoneCheckBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    // 连接信号槽
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ToDoEditDialog::on_buttonBox_accepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

ToDoEditDialog::~ToDoEditDialog() {}

void ToDoEditDialog::setToDoData(const ToDoData &data) {
    m_toDoData = data;
    m_isEditMode = true;

    nameLineEdit->setText(m_toDoData.name());
    int totalSeconds = m_toDoData.expectTime();
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    hoursSpinBox->setValue(hours);
    minutesSpinBox->setValue(minutes);
    priorityComboBox->setCurrentIndex(priorityComboBox->findData(m_toDoData.priority()));
    isDoneCheckBox->setChecked(m_toDoData.isDone());
}
ToDoData ToDoEditDialog::generateToDo(){
    ToDoData newdata;
    newdata.setName(nameLineEdit->text());
    int totalSeconds = hoursSpinBox->value() * 3600 + minutesSpinBox->value() * 60;
    newdata.setExpectTime(totalSeconds);
    newdata.setPriority(static_cast<Priority>(priorityComboBox->currentData().toInt()));
    newdata.setIsDone(isDoneCheckBox->isChecked());
    return newdata;
}



void ToDoEditDialog::setDatabase(MyDataBase *db) {
    m_db = db;
}

void ToDoEditDialog::on_buttonBox_accepted() {
    if (nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "代办名称不能为空！");
        return;
    }

    qDebug()<<"ToDo accept";
    MyDataBase db;db.openDb();
    qDebug()<<"ToDo accept";
    ToDoData oriData = m_toDoData;
    m_toDoData.setName(nameLineEdit->text());
    int totalSeconds = hoursSpinBox->value() * 3600 + minutesSpinBox->value() * 60;
    if (!totalSeconds) {
        QMessageBox::warning(this, "错误", "预期时间不能为空！");
        return;
    }
    m_toDoData.setExpectTime(totalSeconds);
    m_toDoData.setPriority(static_cast<Priority>(priorityComboBox->currentData().toInt()));
    m_toDoData.setIsDone(isDoneCheckBox->isChecked());

    if (m_isEditMode) {
        // 修改模式，更新数据库
        if (db.openDb()) {
            db.modifyToDoData(oriData, m_toDoData);
        }
    } else {
        // 新建模式，插入数据库
        if (db.openDb()) {
            db.insertToDoData(m_toDoData);
        }
    }
    emit editFinished();
    accept();
    //accept();
}
