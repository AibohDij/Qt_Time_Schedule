#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "STCalandarWidget.h"
#include "STDateWidget.h"
#include "timeaxis.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    STCalandarWidget *calendar;
private slots:
    void HaveDateChose(QDate selectedDate);
};
#endif // MAINWINDOW_H
