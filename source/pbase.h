#ifndef PBASE_H
#define PBASE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlDriverCreator>
#include <QSqlDriverCreatorBase>
#include <QSqlDriverPlugin>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QString>


class PBase : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase dbase;
    QString table_users;
    QString table_path;
    QString table_status;
    bool create_tables();
public:
    explicit PBase(QObject *parent = 0);

    bool addUser(QString name);
    bool deleteUser(QString name);
    bool deleteUser(int ID);
    bool updateUser(int ID, int pathID, bool pathAccess);
    bool updateUser(QString user_name, int pathID, bool pathAccess);

    bool addPath(QString name, QString path);
    bool deletePath(int ID);
    bool updatePath(int ID, QString name, QString path);

    int getUserID(QString name);
    QString getUserName(int ID);
    bool getUserAccessPath(QString name, int ID);

    QString getPath(int ID);
    QString getNamePath(int ID);



signals:

public slots:
};

#endif // PBASE_H
