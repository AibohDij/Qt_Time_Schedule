#ifndef FLIPCLOCKWIDGET_H
#define FLIPCLOCKWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "taskdata.h"
#include "mydatabase.h"
class FlipClockWidget : public QWidget {
    Q_OBJECT

public:
    explicit FlipClockWidget(QWidget *parent = nullptr);


public slots:
    void updateTime();

private:
    QLabel *dateLabel;
    QLabel *timeLabel;
    QTimer *timer;
};

class CountdownWidget : public QWidget {
    Q_OBJECT

public:
    explicit CountdownWidget(const ToDoData &toDoData, int size = 400, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateCountdown();
    void pauseCountdown();
    void completeCountdown();
    void setCountdownTime();

private:
    QLabel *nameLabel;
    QLabel *countdownLabel;
    QPushButton *pauseButton;
    QPushButton *completeButton;
    QTimer *timer;
    ToDoData m_toDoData;
    int totalSeconds;
    int remainingSeconds;
    bool isPaused;
    QDateTime startTime=QDateTime::currentDateTime();
    QDateTime endTime=QDateTime::currentDateTime();
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
signals:
    void completed();
};


#endif // FLIPCLOCKWIDGET_H
