#include "FlipClockWidget.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QFont>
#include <QPainter>
#include <QPaintEvent>

FlipClockWidget::FlipClockWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    dateLabel = new QLabel(this);
    dateLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setFont(QFont("Arial", 24, QFont::Bold));
    layout->addWidget(dateLabel);

    timeLabel = new QLabel(this);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setFont(QFont("Arial", 24, QFont::Bold));
    layout->addWidget(timeLabel);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    dateLabel->setText(currentDateTime.toString("yyyy-MM-dd"));
    timeLabel->setText(currentDateTime.toString("HH:mm:ss"));

    // Timer to update time every second
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlipClockWidget::updateTime);
    timer->start(1000); // 1 second
}

void FlipClockWidget::updateTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    dateLabel->setText(currentDateTime.toString("yyyy-MM-dd"));
    timeLabel->setText(currentDateTime.toString("HH:mm:ss"));
}



CountdownWidget::CountdownWidget(const ToDoData &toDoData, int size, QWidget *parent)
    : m_toDoData(toDoData), QWidget(parent), totalSeconds(0), remainingSeconds(0), isPaused(false) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    nameLabel = new QLabel(this);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setFont(QFont("Arial", size / 20, QFont::Bold));
    nameLabel->setText(m_toDoData.name());
    layout->addWidget(nameLabel);

    countdownLabel = new QLabel(this);
    countdownLabel->setAlignment(Qt::AlignCenter);
    countdownLabel->setFont(QFont("Arial", size / 20, QFont::Bold));
    layout->addWidget(countdownLabel, 0, Qt::AlignCenter);

    // Timer to update countdown every second
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CountdownWidget::updateCountdown);

    pauseButton = new QPushButton("暂停", this);
    completeButton = new QPushButton("提前完成", this);
    connect(pauseButton, &QPushButton::clicked, this, &CountdownWidget::pauseCountdown);
    connect(completeButton, &QPushButton::clicked, this, &CountdownWidget::completeCountdown);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(completeButton);
    layout->addLayout(buttonLayout);

    setFixedSize(size, size + 80);
    setCountdownTime();
}

void CountdownWidget::setCountdownTime() {
    totalSeconds = m_toDoData.expectTime();
    remainingSeconds = totalSeconds;
    timer->start(1000); // 1 second
    updateCountdown();
}

void CountdownWidget::updateCountdown() {
    if (!isPaused) {
        remainingSeconds--;

        if (remainingSeconds <= 0) {
            completeCountdown();
        } else {
            int hours = remainingSeconds / 3600;
            int minutes = (remainingSeconds % 3600) / 60;
            int seconds = remainingSeconds % 60;
            countdownLabel->setText(QString("%1:%2:%3")
                                        .arg(hours, 2, 10, QChar('0'))
                                        .arg(minutes, 2, 10, QChar('0'))
                                        .arg(seconds, 2, 10, QChar('0')));
            update(); // Request to update the widget (triggers paintEvent)
        }
    }
}

void CountdownWidget::pauseCountdown() {
    if (isPaused) {
        pauseButton->setText("暂停");
        timer->start(1000); // Resume the timer
    } else {
        pauseButton->setText("继续");
        timer->stop(); // Stop the timer
    }
    isPaused = !isPaused;
}

void CountdownWidget::completeCountdown() {
    countdownLabel->setText("00:00:00");
    timer->stop();
    remainingSeconds = 0;
    update();
    emit completed();
    close();

}

void CountdownWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF outerRect(20, 20, width() - 40, height() - 80 - 40);
    painter.setPen(QPen(Qt::lightGray, 20));
    painter.drawEllipse(outerRect);

    QRectF rect(30, 30, width() - 60, height() - 80 - 60);

    painter.setPen(QPen(Qt::lightGray, 15));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(rect);

    painter.setPen(QPen(Qt::black, 15));
    qreal spanAngle = 360.0 * remainingSeconds / totalSeconds;
    painter.drawArc(rect, 90 * 16, spanAngle * 16); // Negative to draw clockwise
}

