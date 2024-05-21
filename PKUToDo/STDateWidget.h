#ifndef STDATEWIDGET_H
#define STDATEWIDGET_H

#endif // STDATEWIDGET_H
#pragma once
#include <qwidget.h>
#include <QDate>
#include <QPainter>
class STDateWidget :
                     public QWidget
{
    Q_OBJECT
public:
    enum Direction {
        DIR_TOP = 0,
        DIR_BOTTOM,
        DIR_LEFT,
        DIR_RIGHT
    };

    STDateWidget(QWidget* parrent = nullptr);
    ~STDateWidget();
    void SetDate(int year, int month, int day, bool isThisMonth);
    QDate GetCurrentDate();
    void AddNeighbor(STDateWidget* wid,Direction dir);
    void HaveGoodNeighbor(Direction dir);
    void DeleteGoodNgithbor(Direction dir);


private:
    bool isHasGoodNeighbor;
    bool canSelect;
    bool isMoveIn;
    Direction direction;
    QDate currentDate;
    QList<STDateWidget*> neighbors;
    QList<Direction>directions;
private slots:
    void mouseReleaseEvent(QMouseEvent* event) ;
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);

signals:
    void updateCurrentDate(QDate date);
};
