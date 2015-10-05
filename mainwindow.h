#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <source/pbase.h>
#include <source/pcore.h>
#include <QLabel>


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    PBase * pbase;
    PCore * pcore;
    Ui::MainWindow *ui;

    QString user_name;
    //QMap<int, QString> button_name;
    QMap<int, bool> button_run;
    QMap<int, QLabel*> label_name;
    int count_buttons;

    void startPushButton(int ID);
    void syncButtons();
    void setLabel();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

};

#endif // MAINWINDOW_H
