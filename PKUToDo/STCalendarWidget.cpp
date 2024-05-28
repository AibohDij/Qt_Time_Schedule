
#include "STCalendarWidget.h"
#include <QDebug>

STCalendarWidget::STCalendarWidget(QWidget* parrent /* = nullptr */) :QDialog(parrent) {
    //this->setStyleSheet(QString::fromLocal8Bit("font:15px 等线; background-color:rgb(250,250,250)"));
    //this->setStyleSheet(QString::fromLocal8Bit("font:16px 微雅软黑; background-color:rgb(250,250,250)"));
    this->setMinimumSize(800, 450);
    this->setMaximumSize(800, 450);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setMouseTracking(true);
    init();
    QString styleSheet =  // 设置浅灰色背景
        "QPushButton {"
        "border: 1px solid gray;" // 设置按钮边框为2像素宽的黑色实线边框
        "}";

    this->setStyleSheet(styleSheet);
    //this->setStyleSheet(styleSheet);
}

STCalendarWidget::~STCalendarWidget()
{
}

void STCalendarWidget::SetCurrentDate(int year, int month, int day)
{
    currentDate.setDate(year, month, day);
}

QDate STCalendarWidget::GetCurrentDate()
{
    return currentDate;
}

void STCalendarWidget::setTheme(QString s)
{
    theme=s;
}

void STCalendarWidget::FillCalendar()
{
    QDate firstDay;
    firstDay.setDate(currentDate.year(), currentDate.month(), 1);
    int firstnum = firstDay.dayOfWeek();
    //qDebug() << firstnum;
    QDate firstDayOfMonth = firstDay.addDays(-(firstnum - 1));
    for (int i = 0; i < 42; i++) {
        if (i < firstnum-1 || (firstDayOfMonth.month() != currentDate.month())) {
            datewidgets[i]->SetDate(firstDayOfMonth.year(), firstDayOfMonth.month(), firstDayOfMonth.day(), false);
        }
        else {
            datewidgets[i]->SetDate(firstDayOfMonth.year(), firstDayOfMonth.month(), firstDayOfMonth.day(), true);
        }
        firstDayOfMonth = firstDayOfMonth.addDays(1);
    }
}

void STCalendarWidget::initLabels()
{
    for (int i = 0; i < 7; i++) {
        weeklabels[i] = new QLabel(this);
        weeklabels[i]->setGeometry(35 + i*80, 50, 80, 40);
    }
    weeklabels[0]->setText("Mon");
    weeklabels[1]->setText("Tue");
    weeklabels[2]->setText("Wed");
    weeklabels[3]->setText("Thu");
    weeklabels[4]->setText("Fri");
    weeklabels[5]->setText("Sat");
    weeklabels[6]->setText("Sun");
}

void STCalendarWidget::initCalendar()
{

    for (int i = 0; i < 42; i++) {
        datewidgets[i] = new STDateWidget(this);
        datewidgets[i]->setGeometry(10 + i % 7 * 80, 80 + i / 7 * 60, 80, 60);
        connect(datewidgets[i], SIGNAL(updateCurrentDate(QDate)), this, SLOT(HaveDateSelect(QDate)));
        datewidgets[i]->setTheme(theme);

    }
    for (int i = 0; i < 42; i++) {
        if (i / 7 == 0 ) {//第一排
            if (i % 7 == 0) {//第一个
                datewidgets[i]->AddNeighbor(datewidgets[i + 1], STDateWidget::DIR_RIGHT);
            }
            else if (i % 7 == 6) {//最后一个
                datewidgets[i]->AddNeighbor(datewidgets[i - 1], STDateWidget::DIR_LEFT);
            }
            else {
                datewidgets[i]->AddNeighbor(datewidgets[i + 1], STDateWidget::DIR_RIGHT);
                datewidgets[i]->AddNeighbor(datewidgets[i - 1], STDateWidget::DIR_LEFT);
            }
            datewidgets[i]->AddNeighbor(datewidgets[i + 7], STDateWidget::DIR_BOTTOM);
        }
        else if (i / 7 == 5) {//最后一排
            if (i % 7 == 0) {//第一个
                datewidgets[i]->AddNeighbor(datewidgets[i + 1], STDateWidget::DIR_RIGHT);
            }
            else if (i % 7 == 6) {//最后一个
                datewidgets[i]->AddNeighbor(datewidgets[i - 1], STDateWidget::DIR_LEFT);
            }
            else {
                datewidgets[i]->AddNeighbor(datewidgets[i + 1], STDateWidget::DIR_RIGHT);
                datewidgets[i]->AddNeighbor(datewidgets[i - 1], STDateWidget::DIR_LEFT);
            }
            datewidgets[i]->AddNeighbor(datewidgets[i - 7], STDateWidget::DIR_TOP);
        }
        else
        {
            if (i % 7 == 0) {//第一个
                datewidgets[i]->AddNeighbor(datewidgets[i + 1], STDateWidget::DIR_RIGHT);
            }
            else if (i % 7 == 6) {//最后一个
                datewidgets[i]->AddNeighbor(datewidgets[i - 1], STDateWidget::DIR_LEFT);
            }
            else {
                datewidgets[i]->AddNeighbor(datewidgets[i + 1], STDateWidget::DIR_RIGHT);
                datewidgets[i]->AddNeighbor(datewidgets[i - 1], STDateWidget::DIR_LEFT);
            }
            datewidgets[i]->AddNeighbor(datewidgets[i - 7], STDateWidget::DIR_TOP);
            datewidgets[i]->AddNeighbor(datewidgets[i + 7], STDateWidget::DIR_BOTTOM);
        }
    }
    FillCalendar();
}

void STCalendarWidget::init()
{
    currentDate = QDate::currentDate();
    lastYearButton = new QPushButton(this);
    lastYearButton->setGeometry(10, 10, 100, 30);
    //lastYearButton->setText("<<");//上一年
    QSize iconSize(32, 32);
    QIcon Icon1(":/icons/widgets_icons/icons8-rewind-button-round-24.png");
    lastYearButton->setIcon(Icon1);
    lastYearButton->setIconSize(iconSize);
    lastYearButton->setStyleSheet("QPushButton:hover{background:lightGray}""QPushButton:pressed{background:darkGray}");

    lastMonthButton = new QPushButton(this);
    lastMonthButton->setGeometry(120, 10, 100, 30);
    QIcon Icon2(":/icons/widgets_icons/icons8-last-page-24.png");
    lastMonthButton->setIcon(Icon2);
    lastMonthButton->setIconSize(iconSize);//上一个月
    lastMonthButton->setStyleSheet("QPushButton:hover{background:lightGray}""QPushButton:pressed{background:darkGray}");

    cdlabel = new QLabel(this);
    cdlabel->setGeometry(255, 10, 100, 40);
    cdlabel->setObjectName("DateLabel_calender");
    cdlabel->setText(getFormatMonth());//当前时间

    nextMonthButton = new QPushButton(this);
    nextMonthButton->setGeometry(360, 10, 100, 30);
    //nextMonthButton->setText(">");// 下一月
    QIcon Icon3(":/icons/widgets_icons/icons8-next-page-24.png");
    nextMonthButton->setIcon(Icon3);
    nextMonthButton->setIconSize(iconSize);
    nextMonthButton->setStyleSheet("QPushButton:hover{background:lightGray}""QPushButton:pressed{background:darkGray}");

    nextYearButton = new QPushButton(this);
    nextYearButton->setGeometry(470, 10, 100, 30);
    //nextYearButton->setText(">>");//下一年
    QIcon Icon4(":/icons/widgets_icons/icons8-fast-forward-round-24.png");
    nextYearButton->setIcon(Icon4);
    nextYearButton->setIconSize(iconSize);
    nextYearButton->setStyleSheet("QPushButton:hover{background:lightGray}""QPushButton:pressed{background:darkGray}");

    yearLineEdit =  new QLineEdit(QString::number(currentDate.year()), this);//设置年
    yearLineEdit->setValidator(new QIntValidator(2000, 3000, this));//年区间范围
    yearLineEdit->setGeometry(580,10,60,30);
    yearLineEdit->setObjectName("YearLineEdit");

    monthSpinBox = new QSpinBox(this);//设置月
    monthSpinBox->setMinimum(1); // 设置最小月份
    monthSpinBox->setMaximum(12); // 设置最大月份
    monthSpinBox->setValue(currentDate.month()); // 设置当前月份
    monthSpinBox->setGeometry(650,10,50,30);
    monthSpinBox->setObjectName("MonthSpinBox");


    setYearMonth = new QPushButton( this);
    setYearMonth->setGeometry(710, 10, 100, 30); // 增加宽度为 70 像素
    QIcon Icon5(":/icons/widgets_icons/icons8-enter2-50.png");
    setYearMonth->setIcon(Icon5);
    setYearMonth->setIconSize(QSize(24, 24));
    setYearMonth->setStyleSheet("QPushButton:hover{background:lightGray}""QPushButton:pressed{background:darkGray}");
    // 设置样式表
    //connect(lastYearButton, SIGNAL(clicked()), this, SLOT(JumpLastYear()));
    connect(lastYearButton, &QPushButton::clicked, this, &STCalendarWidget::JumpLastYear);
    connect(lastMonthButton, &QPushButton::clicked, this, &STCalendarWidget::JumpLastMonth);
    connect(nextMonthButton, &QPushButton::clicked, this, &STCalendarWidget::JumpNextMonth);
    connect(nextYearButton, &QPushButton::clicked, this, &STCalendarWidget::JumpNextYear);
    //new slots
    connect(setYearMonth, &QPushButton::clicked, this, &STCalendarWidget::SetDate);
    initLabels();
    initCalendar();
    //排版布局
    QVBoxLayout * mainLayout = new QVBoxLayout();//主排版界面
    QGridLayout *DateLayout= new QGridLayout();//日期对象网格界面
    QHBoxLayout *ButtonLayout = new QHBoxLayout();//按钮水平横排
    //QHBoxLayout *LabelsLayout = new QHBoxLayout();//星期标签水平横排
    //ButtonLayout->addSpacerItem(new QSpacerItem(100, 0));
    ButtonLayout->addStretch();
    ButtonLayout->addWidget(lastYearButton);    ButtonLayout->addWidget(lastMonthButton);ButtonLayout->addStretch();
    ButtonLayout->addWidget(cdlabel); ButtonLayout->addStretch();   ButtonLayout->addWidget(nextMonthButton);
    ButtonLayout->addWidget(nextYearButton);
    ButtonLayout->addStretch();
    //ButtonLayout->addStretch();
    ButtonLayout->addSpacerItem(new QSpacerItem(100, 0));
    ButtonLayout->addWidget(yearLineEdit);
    ButtonLayout->addWidget(monthSpinBox);    ButtonLayout->addWidget(setYearMonth);
    mainLayout->addLayout(ButtonLayout);
    // for(auto weeklabel: weeklabels){
    //     LabelsLayout->addWidget(weeklabel);
    // }
    // mainLayout->addLayout(LabelsLayout);
    int index=0;
    for(int col=0;col<7;col++){
        weeklabels[col]->setAlignment(Qt::AlignCenter);
        DateLayout->addWidget(weeklabels[col],0,col);
    }
    for(int row=1;row<=6;row++){
        for(int col=0;col<7;col++){
            datewidgets[index]->setMinimumSize(80, 60);
            DateLayout->addWidget(datewidgets[index],row,col);
            index++;
        }
    }

    DateLayout->setAlignment(Qt::AlignHCenter);
    for (int row = 0; row < 7; row++) {
        DateLayout->setRowStretch(row, 1);
    }

    // 设置所有列的拉伸因子为1，表示所有列都会随着窗口的水平拉伸而拉伸
    for (int col = 0; col < 7; col++) {
        DateLayout->setColumnStretch(col, 1);
    }
    mainLayout->addLayout(DateLayout);
    mainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize); // 设置主排版界面的大小约束
    mainLayout->setContentsMargins(0, 0, 0, 0); // 设置边距为0
    setLayout(mainLayout);

}
QString STCalendarWidget::getFormatMonth()
{
    QString ans = "";
    int currentYear = currentDate.year();
    int currentMonth = currentDate.month();

    // 将年份和月份转换为QString字符串
    ans = QString("%1年%2月").arg(currentYear).arg(currentMonth);
    return ans;
}
void STCalendarWidget::HaveDateSelect(QDate date)
{
    qDebug() << date;
    emit DateSelectSignal(date);
}
void STCalendarWidget::JumpLastYear()
{
    currentDate = currentDate.addYears(-1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void STCalendarWidget::JumpLastMonth()
{
    currentDate = currentDate.addMonths(-1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void STCalendarWidget::JumpNextMonth()
{
    currentDate = currentDate.addMonths(1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void STCalendarWidget::JumpNextYear()
{
    currentDate = currentDate.addYears(1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}

void STCalendarWidget::SetDate()
{
    // 获取年份输入框的文本并转换为整数
    int year = yearLineEdit->text().toInt();
    // 获取月份微调框的当前值
    int month = monthSpinBox->value();
    // 使用获取的年份和月份设置当前日期
    currentDate.setDate(year, month, 1);
    FillCalendar();
    cdlabel->setText(getFormatMonth());
}
