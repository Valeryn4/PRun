#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PBase b;
    b.addUser("LOL");
    b.addUser("ololo");
    b.addUser("gucking");

    b.updateUser("LOL", 3, true);
    b.updateUser(2, 10, false);

    b.deleteUser(1);
    b.deleteUser("ololo");

    b.addPath("path1", "/path/to/fuck");
    b.addPath("calc", "path/to/calk");
    b.addPath("WAT", "WAT!");
    b.updatePath(1, "pook", "/path/lol/lol");
   // b.deletePath(1);

    qDebug() << b.getUserName(1);
    qDebug() << b.getUserID("LOL");
    qDebug() << b.getUserID("gucking");
    qDebug() << b.getUserAccessPath("LOL", 3);
    qDebug() << b.getUserAccessPath("LOL", 10);
    qDebug() << b.getPath(2);
    qDebug() << b.getNamePath(2);

    ui->tableView->setModel(b.getTableModel("path", this));
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
