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

#include <QSqlTableModel>
#include <QSqlQueryModel>




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
    ~PBase();

    bool addUser(QString name);
    bool deleteUser(QString name);
    bool deleteUser(int ID);
    bool updateUser(int ID, int pathID, bool pathAccess);
    bool updateUser(QString user_name, int pathID, bool pathAccess);
    bool existsUser(QString user_name);

    bool addPath(QString name, QString path);
    bool deletePath(int ID);
    bool updatePath(int ID, QString name, QString path);

    int getUserID(QString name);
    QString getUserName(int ID);
    bool getUserAccessPath(QString name, int pathID);

    QString getPath(int ID);
    QString getNamePath(int ID);
    int getCountPath();

    QSqlQueryModel * getQueryModel(QString table_name, QObject *obj = 0);
    QSqlTableModel * getTableModel(QString table_name, QObject *obj = 0);

signals:

public slots:

};

#endif // PBASE_H
