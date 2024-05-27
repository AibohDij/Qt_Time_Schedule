#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QGroupBox>
#include <QRadioButton>
#include <QDesktopServices>

#include "chartwidget.h"
#include "mydatabase.h"
#include "taskdata.h"
#include "task.h"
#include "STCalandarWidget.h"
#include "STDateWidget.h"
#include "timeaxis.h"
#include "searchwidget.h"
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
    void loadTheme(const QString& themeName);
    QString currentTheme = "blueStyle.qss";
private:
    Ui::MainWindow *ui;
    STCalandarWidget *calendar;

private slots:

    void HaveDateChose(QDate selectedDate);
    void onTabWidgetCurrentChanged(int index);
    void onThemeChanged(const QString& themeName);
    void on_pushButton_intro_clicked();
};
#endif // MAINWINDOW_H
