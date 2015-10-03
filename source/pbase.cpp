#include "pbase.h"

PBase::PBase(QObject *parent) : QObject(parent)
{

    table_path      = "path";
    table_users     = "users";
    table_status    = "status";

    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("prun.sqlite");

    create_tables();


}

bool PBase::create_tables() {
    if (!dbase.open())
        qDebug() << "PBase() open prun.sqlite fail!\n"
                 << "ERROR: " << dbase.lastError().text();
    else
        qDebug() << "PBase() open prun.sqlite access \n"
                 << "VALIDE: " << dbase.isValid();

    QString query_create_table_user = "CREATE TABLE IF NOT EXISTS " + table_users + "(" +
                  "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                  "user_name CHAR(30) NOT NULL UNIQUE," +
                  "path1 BOOL," +
                  "path2 BOOL," +
                  "path3 BOOL," +
                  "path4 BOOL," +
                  "path5 BOOL," +
                  "path6 BOOL," +
                  "path7 BOOL," +
                  "path8 BOOL," +
                  "path9 BOOL," +
                  "path10 BOOL," +
                  "path11 BOOL," +
                  "path12 BOOL," +
                  "path13 BOOL," +
                  "path14 BOOL," +
                  "path15 BOOL," +
                  "path16 BOOL," +
                  "path17 BOOL," +
                  "path18 BOOL," +
                  "path19 BOOL," +
                  "path20 BOOL" + ");";

    QString query_create_table_path = "CREATE TABLE IF NOT EXISTS " + table_path + "(" +
                  "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                  "name CHAR(30)," +
                  "path CHAR(64)" + ");";

    QString query__create_table_status = "CREATE TABLE IF NOT EXISTS " + table_status + "(" +
            "id INTEGER PRIMARY KEY AUTOINCREMENT," +
            "id_user INT," +
            "id_path INT," +
            "process_status CHAR(5)" + ");";

    QSqlQuery query_a;

    if (query_a.exec(query_create_table_path))
        qDebug() << "PBase() create table or exists " << table_path;
    else
        qDebug() << "PBase() no create or table exec " << table_path << "\n"
                 << "ERROR: " << query_a.lastError().text();
    if (query_a.exec(query_create_table_user))
        qDebug() << "PBase() create table or exists " << table_users;
    else
        qDebug() << "PBase() no create or table exec " << table_users << "\n"
                 << "ERROR: " << query_a.lastError().text();
    if (query_a.exec(query__create_table_status))
        qDebug() << "PBase() create table or exists" << table_status;
    else
        qDebug() << "PBase() no create or table exec " << table_status << "\n"
                 << "ERROR: " << query_a.lastError().text();

    query_a.clear();
    dbase.close();

    return true;

}

bool PBase::addUser(QString name) {

    if (!dbase.open())
        qDebug() << "PBase::addUser() open prun.sqlite fail!\n"
                 << "ERROR: " << dbase.lastError().text();
    else
        qDebug() << "PBase::addUser() open prun.sqlite access \n"
                 << "VALIDE: " << dbase.isValid();

    QSqlQuery query_a;
    QString query_user_insert = "INSERT INTO " + table_users + "(user_name) VALUES('"+ name +"');";

    if (query_a.exec(query_user_insert)) {
        qDebug() << "PBase::addUser() insert " << name << " to " << table_users;
        dbase.close();
        qDebug() << "PBase::addUser() close prun.sqlite";
        return true;
    }
    else {
        qDebug() << "PBase::addUser() FAIL insert " << name << " to " << table_users << "\n"
                 << "ERROR: " << query_a.lastError().text();
        dbase.close();
        qDebug() << "PBase::addUser() close prun.sqlite";
        return false;
    }

}

bool PBase::deleteUser(QString name) {
    if (!dbase.open())
        qDebug() << "PBase::deleteUser() open prun.sqlite fail!\n"
                 << "ERROR " << dbase.lastError().text();
    else
        qDebug() << "PBase::deleteUser() open prun.sqlite access \n"
                 << "VALIDE: " << dbase.isValid();

    QString query_delete_user = "DELETE FROM " + table_users + " WHERE user_name = '" + name + "' ;";
    QSqlQuery query_a;
    if (query_a.exec(query_delete_user)) {
        qDebug() << "PBase::deleteUser() DELETE access name " << name << " from table " + table_users;
        dbase.close();
        return true;
    }
    else {
        qDebug() << "PBase::deleteUser() DELETE FAIL! name " << name << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        dbase.close();
        qDebug() << "PBase::deleteUser() close prun.sqlite";
        return false;
    }

}

bool PBase::deleteUser(int ID) {
    if (!dbase.open())
        qDebug() << "PBase::deleteUser() open prun.sqlite fail!\n"
                 << "ERROR " << dbase.lastError().text();
    else
        qDebug() << "PBase::deleteUser() open prun.sqlite access \n"
                 << "VALIDE: " << dbase.isValid();

    QString query_delete_user = "DELETE FROM " + table_users + " WHERE id = '" + ID + "' ;";
    QSqlQuery query_a;
    if (query_a.exec(query_delete_user)) {
        qDebug() << "PBase::deleteUser() DELETE access id " << ID << " from table " + table_users;
        dbase.close();
        return true;
    }
    else {
        qDebug() << "PBase::deleteUser() DELETE FAIL! id " << ID << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        dbase.close();
        qDebug() << "PBase::deleteUser() close prun.sqlite";
        return false;
    }

}

bool PBase::updateUser(QString name, int pathID, bool pathAccess) {
    if (!dbase.open())
        qDebug() << "PBase::updateUser() open prun.sqlite fail!\n"
                 << "ERROR " << dbase.lastError().text();
    else
        qDebug() << "PBase::updateUser() open prun.sqlite access \n"
                 << "VALIDE: " << dbase.isValid();
    QString query_update_user = "UPDATE %1 SET path%2 = %3 WHERE user_name = '%4';";
    if (pathAccess == true)
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(1), name);
    else
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(0), name);
    QSqlQuery query_a;

    if (query_a.exec(query_update_user)) {
        qDebug() << "PBase::updateUser() UPDATE access name " << name << " from table " + table_users;
        dbase.close();
        return true;
    }
    else {
        qDebug() << "PBase::updateUser() UPDATE FAIL! name " << name << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        dbase.close();
        qDebug() << "PBase::updateUser() close prun.sqlite";
        return false;
    }
}

bool PBase::updateUser(int ID, int pathID, bool pathAccess) {
    if (!dbase.open())
        qDebug() << "PBase::updateUser() open prun.sqlite fail!\n"
                 << "ERROR " << dbase.lastError().text();
    else
        qDebug() << "PBase::updateUser() open prun.sqlite access \n"
                 << "VALIDE: " << dbase.isValid();
    QString query_update_user = "UPDATE %1 SET path%2 = %3 WHERE id = %4;";
    if (pathAccess == true)
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(1), QString::number(ID));
    else
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(0), QString::number(ID));

    QSqlQuery query_a;

    if (query_a.exec(query_update_user)) {
        qDebug() << "PBase::updateUser() UPDATE access id " << ID << " from table " + table_users;
        dbase.close();
        return true;
    }
    else {
        qDebug() << "PBase::updateUser() UPDATE FAIL! id " << ID << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        dbase.close();
        qDebug() << "PBase::updateUser() close prun.sqlite";
        return false;
    }
}
