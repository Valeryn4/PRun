#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QDir>

#define PATHS 20


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pbase = new PBase(this);
    pcore = new PCore(PATHS, this);

    user_name = QDir::home().dirName();

    if (!pbase->existsUser(user_name)) {
        pbase->addUser(user_name);
        pbase->updateUser(user_name, 1, true);

    }

    //Заполняем контейнеры Pcore
    setLabel();
    count_buttons = 0;
    for (int i = 1; i < PATHS; i++ )  {
        //button_name[i] = " none ";
        button_run[i] = false;
        if (pbase->getUserAccessPath(user_name, i)){
            qDebug() << " pbase access path " << i << " = " << pbase->getUserAccessPath(user_name, i)
                     << " i == " << i;
            if (pcore->addProcessPath(pbase->getPath(i))) {
                count_buttons++;
                pcore->setAccess(count_buttons);
                //button_name[count_buttons] = pbase->getNamePath(i);
                label_name[count_buttons]->setText(pbase->getNamePath(i));
            }
        }
    }
    syncButtons();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabel() {
    label_name[1] = ui->label_1;
    label_name[2] = ui->label_2;
    label_name[3] = ui->label_3;
    label_name[4] = ui->label_4;
    label_name[5] = ui->label_5;
    label_name[6] = ui->label_6;
    label_name[7] = ui->label_7;
    label_name[8] = ui->label_8;
    label_name[9] = ui->label_9;
}

void MainWindow::syncButtons() {
    QString running = "Закрыть";
    QString no_running = "Запустить";
    if (button_run[1] == true) ui->pushButton_1->setText(running);
    else ui->pushButton_1->setText(no_running);

    if (button_run[2] == true) ui->pushButton_2->setText(running);
    else ui->pushButton_2->setText(no_running);

    if (button_run[3] == true) ui->pushButton_3->setText(running);
    else ui->pushButton_3->setText(no_running);

    if (button_run[4] == true) ui->pushButton_4->setText(running);
    else ui->pushButton_4->setText(no_running);

    if (button_run[5] == true) ui->pushButton_5->setText(running);
    else ui->pushButton_5->setText(no_running);

    if (button_run[6] == true) ui->pushButton_6->setText(running);
    else ui->pushButton_6->setText(no_running);

    if (button_run[7] == true) ui->pushButton_7->setText(running);
    else ui->pushButton_7->setText(no_running);

    if (button_run[8] == true) ui->pushButton_8->setText(running);
    else ui->pushButton_8->setText(no_running);

    if (button_run[9] == true) ui->pushButton_9->setText(running);
    else ui->pushButton_9->setText(no_running);

}

void MainWindow::startPushButton(int ID) {

    if (ID == 0){
        pcore->killAll();
        qApp->exit();

    }
    else if (button_run[ID] == false) {
        if (pcore->runProcess(ID))
            button_run[ID] = true;
    }
    else if (button_run[ID] == true){
        if(!pcore->kill(ID))
            qDebug() << "fail kill process " << ID;
        button_run[ID] = false;
    }

    syncButtons();
}

//=========SLOTS========
void MainWindow::on_pushButton_1_clicked() { startPushButton(1);}
void MainWindow::on_pushButton_2_clicked() { startPushButton(2);}
void MainWindow::on_pushButton_3_clicked() { startPushButton(3);}
void MainWindow::on_pushButton_4_clicked() { startPushButton(4);}
void MainWindow::on_pushButton_5_clicked() { startPushButton(5);}
void MainWindow::on_pushButton_6_clicked() { startPushButton(6);}
void MainWindow::on_pushButton_7_clicked() { startPushButton(7);}
void MainWindow::on_pushButton_8_clicked() { startPushButton(8);}
void MainWindow::on_pushButton_9_clicked() { startPushButton(9);}

void MainWindow::on_pushButton_0_clicked() { startPushButton(0);}

