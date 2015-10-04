#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <source/pbase.h>
#include <source/pcore.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    PBase * pbase;
    PCore * pcore;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
