
#include "STDateWidget.h"
#include <QMouseEvent>
#include <QLinearGradient>
STDateWidget::STDateWidget(QWidget* parrent /* = nullptr */) :QWidget(parrent)
{

    this->setMouseTracking(true);
    isMoveIn = false;
    //qDebug() << "make";
    //this->setGeometry(0, 0, 180, 160);
    isHasGoodNeighbor = false;
    //this->setStyleSheet("background-color:red");
    //setMouseTracking(true);
    QString styleSheet = "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
                         "stop: 0 #3498db, stop: 1 #87CEFA); "  // 渐变背景
                         "color: white; "  // 文字颜色
                         "border: 2px solid transparent; "  // 透明边框，用于应用渐变
                         "border-radius: 10px; "  // 圆角
                         "padding: 5px 10px; "  // 内边距
                         "font-size: 15px; "  // 字体大小
                         "font-weight: bold; "  // 字体粗细
                         "font-family: 'STFangsong', sans-serif;";  // 字体

    this->setStyleSheet(styleSheet);
}
STDateWidget::~STDateWidget()
{
}

void STDateWidget::SetDate(int year, int month, int day, bool isThisMonth)
{
    currentDate.setDate(year, month, day);
    canSelect = isThisMonth;

    update();
}

QDate STDateWidget::GetCurrentDate()
{
    return currentDate;
}

void STDateWidget::AddNeighbor(STDateWidget* wid, Direction dir)
{
    neighbors.append(wid);
    directions.append(dir);
}

void STDateWidget::HaveGoodNeighbor(Direction dir)
{
    isHasGoodNeighbor = true;
    direction = dir;
    update();
}

void STDateWidget::DeleteGoodNgithbor(Direction dir)
{
    isHasGoodNeighbor = false;
    direction = dir;
    update();
}

void STDateWidget::setTheme(QString s)
{
    theme=s;
}

void STDateWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (canSelect) {
        emit updateCurrentDate(currentDate);
    }

}

void STDateWidget::enterEvent(QEnterEvent* event)//QT6中事件类型发生了变化
{
    //qDebug() << "Enter event triggered."; // 调试输出语句
    isMoveIn = true;
    for (int i = 0; i < neighbors.count(); i++) {
        neighbors[i]->HaveGoodNeighbor(directions[i]);
    }
    update(); //  update() 函数重绘
}

void STDateWidget::leaveEvent(QEvent* event)
{
    //qDebug() << "Leave event triggered."; // 调试输出语句
    isMoveIn = false;
    for (int i = 0; i < neighbors.count(); i++) {
        neighbors[i]->DeleteGoodNgithbor(directions[i]);
    }
    update();
}

void STDateWidget::paintEvent(QPaintEvent* event)//特效 不用动 可以调大小或颜色
{
    //return;
    QPainter painter(this);
    painter.save();

    //painter.setBrush(QColor(140,217,255,150)); // 设置为白色背景
     // 设置为白色背景

    // 绘制矩形背景
    if(theme=="blue"){
        painter.setBrush(QColor(140,217,255,150));
    }
    else{
        painter.setBrush(QColor(180, 180, 180, 120));
    }
    painter.drawRoundedRect(rect(),10,10);

    //painter.restore();
    //Border
    QColor borderColor(180, 180, 180, 120); // 浅灰色，透明度为120
    QPen borderPen(borderColor);
    if (currentDate == QDate::currentDate()) {
        borderColor = QColor(255, 100, 100, 150); // 浅红色，透明度为150 //特别标注出今天
        borderPen.setColor(borderColor);
        painter.setPen(borderPen);
    }
    borderPen.setWidth(3);
    painter.setPen(borderPen);

    // Calculate border radius (assuming uniform radius for all corners)
    int borderRadius = 10; // Adjust this value as needed

    // Calculate the adjusted rectangle to account for border width
    QRect adjustedRect = rect().adjusted(1, 1, -1, -1);

    // Draw rounded rectangle
    painter.drawRoundedRect(adjustedRect, borderRadius, borderRadius);

    int xx = 1;
    int yy = 1;
    int ww = this->geometry().width();
    int hh = this->geometry().height();
    if (isMoveIn) {
        QPen pen;
        painter.setBrush(QColor(135,206,235, 200));
//        painter.setBrush(QColor(180, 180, 180, 120));
        painter.drawRoundedRect(rect(),10,10);

        pen.setBrush(QColor(0, 200, 250, 200));
        //pen.setBrush(QColor(180, 180, 180, 120));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRoundedRect(xx + 2, yy + 2, ww - 4, hh - 4, 10, 10);
    }
    else {
        if (isHasGoodNeighbor)
        {
            QPen pen;
            pen.setBrush(QColor(255, 255, 255, 0));
            pen.setWidth(0);
            painter.setPen(pen);
            QLinearGradient line_left_top2bottom(xx + 2, yy + 2, xx + 2, yy + hh - 6);//左。
            line_left_top2bottom.setColorAt(0.0, Qt::white);
            line_left_top2bottom.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_left_bottom2top( xx + 2, yy + hh - 6, xx + 2, yy + 2);//左。
            line_left_bottom2top.setColorAt(0.0, Qt::white);
            line_left_bottom2top.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_right_top2bottpm(xx + ww - 6, yy + 2, xx + ww - 6, yy + hh - 6);
            line_right_top2bottpm.setColorAt(0.0, Qt::white);
            line_right_top2bottpm.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_right_bottom2top(xx + ww - 6, yy + hh - 6, xx + ww - 6, yy + 2);
            line_right_bottom2top.setColorAt(0.0, Qt::white);
            line_right_bottom2top.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_top_left2right(xx + 2, yy + 2, xx + ww - 6, yy + 2);
            line_top_left2right.setColorAt(0.0, Qt::white);
            line_top_left2right.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_top_right2left(xx + ww - 6, yy + 2, xx + 2, yy + 2);
            line_top_right2left.setColorAt(0.0, Qt::white);
            line_top_right2left.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_bottom_left2right(xx + 2, yy + hh - 6, xx + ww - 6, yy + hh - 6);
            line_bottom_left2right.setColorAt(0.0, Qt::white);
            line_bottom_left2right.setColorAt(1.0, QColor(0, 200, 250, 100));
            QLinearGradient line_bottom_right2left(xx + ww - 6, yy + hh - 6, xx + 2, yy + hh - 6);
            line_bottom_right2left.setColorAt(0.0, Qt::white);
            line_bottom_right2left.setColorAt(1.0, QColor(0, 200, 250, 100));
            QRect rectTop(xx + 2, yy + 2, ww - 6, 2);
            QRect rectBottom(xx + 2, yy + hh - 4, ww - 4, 2);
            QRect rectLeft(xx + 2, yy + 2, 2, hh - 6);
            QRect rectRight(xx + ww - 4, yy + 2, 2, hh - 6);
            switch (direction)
            {
            case STDateWidget::DIR_TOP:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRoundedRect(rectBottom,10,10);
                painter.setBrush(line_left_top2bottom);
                painter.drawRoundedRect(rectLeft,10,10);
                painter.setBrush(line_right_top2bottpm);
                painter.drawRoundedRect(rectRight,10,10);
                break;
            case STDateWidget::DIR_BOTTOM:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRoundedRect(rectTop,10,10);
                painter.setBrush(line_left_bottom2top);
                painter.drawRoundedRect(rectLeft,10,10);
                painter.setBrush(line_right_bottom2top);
                painter.drawRoundedRect(rectRight,10,10);
                break;
            case STDateWidget::DIR_LEFT:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRoundedRect(rectRight,10,10);
                painter.setBrush(line_top_left2right);
                painter.drawRoundedRect(rectTop,10,10);
                painter.setBrush(line_bottom_left2right);
                painter.drawRoundedRect(rectBottom,10,10);
                break;
            case STDateWidget::DIR_RIGHT:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRoundedRect(rectLeft,10,10);
                painter.setBrush(line_top_right2left);
                painter.drawRoundedRect(rectTop,10,10);
                painter.setBrush(line_bottom_right2left);
                painter.drawRoundedRect(rectBottom,10,10);
                break;
            default:
                break;
            }
        }
        /*   QPen pen;
           pen.setBrush(QColor(255, 255, 255, 255));
           pen.setWidth(2);
           painter.setPen(pen);
           painter.drawRect(this->geometry());*/
    }
    painter.restore();
    if (canSelect) {
        QPen pen2;
        pen2.setBrush(QColor(0, 0, 0));
        painter.setPen(pen2);
        painter.drawText(ww/2 - 10, hh/2, QString::number(currentDate.day()));
    }
    else {
        QPen pen2;
        pen2.setBrush(QColor(200, 200, 200));
        painter.setPen(pen2);
        painter.drawText(ww/2- 10, hh/2, QString::number(currentDate.day()));
    }
    //painter
}
