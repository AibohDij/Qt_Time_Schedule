
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

    //Border
    QColor borderColor(180, 180, 180, 120); // 浅灰色，透明度为150
    QPen borderPen(borderColor);
    if (currentDate == QDate::currentDate()) {
        borderColor = QColor(255, 100, 100, 150); // 浅红色，透明度为150 //特别标注出今天
        borderPen.setColor(borderColor);
        painter.setPen(borderPen);
    }
    borderPen.setWidth(2);
    painter.setPen(borderPen);

    painter.drawRect(rect().adjusted(1, 1, -1, -1));

    int xx = 1;
    int yy = 1;
    int ww = this->geometry().width();
    int hh = this->geometry().height();
    if (isMoveIn) {
        QPen pen;
        pen.setBrush(QColor(0, 200, 250, 200));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(xx +2 ,yy +2,ww-4,hh-4);
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
                painter.drawRect(rectBottom);
                painter.setBrush(line_left_top2bottom);
                painter.drawRect(rectLeft);
                painter.setBrush(line_right_top2bottpm);
                painter.drawRect(rectRight);
                break;
            case STDateWidget::DIR_BOTTOM:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRect(rectTop);
                painter.setBrush(line_left_bottom2top);
                painter.drawRect(rectLeft);
                painter.setBrush(line_right_bottom2top);
                painter.drawRect(rectRight);
                break;
            case STDateWidget::DIR_LEFT:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRect(rectRight);
                painter.setBrush(line_top_left2right);
                painter.drawRect(rectTop);
                painter.setBrush(line_bottom_left2right);
                painter.drawRect(rectBottom);
                break;
            case STDateWidget::DIR_RIGHT:
                painter.setBrush(QColor(0, 200, 250, 100));
                painter.drawRect(rectLeft);
                painter.setBrush(line_top_right2left);
                painter.drawRect(rectTop);
                painter.setBrush(line_bottom_right2left);
                painter.drawRect(rectBottom);
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
