#include "mainwindow.h"
#include <QApplication>
#include "source/pbase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
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
    b.deletePath(1);
    w.show();



    return a.exec();
}
