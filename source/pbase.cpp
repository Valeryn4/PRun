#include "pbase.h"

PBase::PBase(QObject *parent) : QObject(parent)
{

    table_path      = "path";
    table_users     = "users";
    table_status    = "status";

    dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("prun.sqlite");
    if (!dbase.open())
        qDebug() << "Fail open prun.sqlite";

    create_tables();


}

PBase::~PBase() {
    dbase.close();
}

//Create tables
bool PBase::create_tables() {
    QString query_create_table_user = "CREATE TABLE IF NOT EXISTS " + table_users + "(" +
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," +
                  "user_name CHAR(30) NOT NULL UNIQUE," +
                  "path1 BOOL DEFAULT 0," +
                  "path2 BOOL DEFAULT 0," +
                  "path3 BOOL DEFAULT 0," +
                  "path4 BOOL DEFAULT 0," +
                  "path5 BOOL DEFAULT 0," +
                  "path6 BOOL DEFAULT 0," +
                  "path7 BOOL DEFAULT 0," +
                  "path8 BOOL DEFAULT 0," +
                  "path9 BOOL DEFAULT 0," +
                  "path10 BOOL DEFAULT 0," +
                  "path11 BOOL DEFAULT 0," +
                  "path12 BOOL DEFAULT 0," +
                  "path13 BOOL DEFAULT 0," +
                  "path14 BOOL DEFAULT 0," +
                  "path15 BOOL DEFAULT 0," +
                  "path16 BOOL DEFAULT 0," +
                  "path17 BOOL DEFAULT 0," +
                  "path18 BOOL DEFAULT 0," +
                  "path19 BOOL DEFAULT 0," +
                  "path20 BOOL DEFAULT 0" + ");";

    QString query_create_table_path = "CREATE TABLE IF NOT EXISTS " + table_path + "(" +
                  "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," +
                  "name CHAR(30) NOT NULL UNIQUE," +
                  "path CHAR(64)" + ");";

    QString query__create_table_status = "CREATE TABLE IF NOT EXISTS " + table_status + "(" +
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," +
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

    return true;

}


//===========
//Users param
//===========

bool PBase::addUser(QString name) {

    QSqlQuery query_a;
    QString query_user_insert = "INSERT INTO " + table_users + "(user_name) VALUES('"+ name +"');";

    if (query_a.exec(query_user_insert)) {
        qDebug() << "PBase::addUser() insert " << name << " to " << table_users;
        return true;
    }
    else {
        qDebug() << "PBase::addUser() FAIL insert " << name << " to " << table_users << "\n"
                 << "ERROR: " << query_a.lastError().text();
        return false;
    }

}


bool PBase::deleteUser(QString name) {

    QString query_delete_user = "DELETE FROM " + table_users + " WHERE user_name = '" + name + "' ;";
    QSqlQuery query_a;
    if (query_a.exec(query_delete_user)) {
        qDebug() << "PBase::deleteUser() DELETE access name " << name << " from table " + table_users;
        return true;
    }
    else {
        qDebug() << "PBase::deleteUser() DELETE FAIL! name " << name << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }

}


bool PBase::deleteUser(int ID) {

    QString query_delete_user = "DELETE FROM " + table_users + " WHERE id = '" + ID + "' ;";
    QSqlQuery query_a;
    if (query_a.exec(query_delete_user)) {
        qDebug() << "PBase::deleteUser() DELETE access id " << ID << " from table " + table_users;
        return true;
    }
    else {
        qDebug() << "PBase::deleteUser() DELETE FAIL! id " << ID << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }

}


bool PBase::updateUser(QString name, int pathID, bool pathAccess) {

    QString query_update_user = "UPDATE %1 SET path%2 = %3 WHERE user_name = '%4';";
    if (pathAccess == true)
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(1), name);
    else
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(0), name);
    QSqlQuery query_a;

    if (query_a.exec(query_update_user)) {
        qDebug() << "PBase::updateUser() UPDATE access name " << name << " from table " + table_users;
        return true;
    }
    else {
        qDebug() << "PBase::updateUser() UPDATE FAIL! name " << name << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }
}


bool PBase::updateUser(int ID, int pathID, bool pathAccess) {

    QString query_update_user = "UPDATE %1 SET path%2 = %3 WHERE id = %4;";
    if (pathAccess == true)
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(1), QString::number(ID));
    else
        query_update_user = query_update_user.arg(table_users, QString::number(pathID), QString::number(0), QString::number(ID));

    QSqlQuery query_a;

    if (query_a.exec(query_update_user)) {
        qDebug() << "PBase::updateUser() UPDATE access id " << ID << " from table " + table_users;
        return true;
    }
    else {
        qDebug() << "PBase::updateUser() UPDATE FAIL! id " << ID << " from table " + table_users
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }
}

//==========
//Path param
//==========
bool PBase::addPath(QString name, QString path) {
    QString query_add_path = "INSERT INTO %1(name, path) VALUES('%2', '%3') ;";
    query_add_path = query_add_path.arg(table_path, name, path);
    QSqlQuery query_a;

    if (query_a.exec(query_add_path)) {
        qDebug() << "PBase::addPath() add access name " << name << " from table " + table_path;
        return true;
    }
    else {
        qDebug() << "PBase::addPath() add FAIL! name " << name << " from table " + table_path
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }
}


bool PBase::deletePath(int ID) {

    QString query_delete_path = "DELETE FROM %1 WHERE id = %2 ;";
    query_delete_path = query_delete_path.arg(table_path, QString::number(ID));
    QSqlQuery query_a;

    if (query_a.exec(query_delete_path)) {
        qDebug() << "PBase::deletePath() delete access id " << ID << " from table " + table_path;
        return true;
    }
    else {
        qDebug() << "PBase::deletePath() delete FAIL! id " << ID << " from table " + table_path
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }
}

bool PBase::updatePath(int ID, QString name, QString path) {

    QString query_update_path = "UPDATE %1 SET name = '%2', path = '%3' WHERE id = %4 ;";
    query_update_path = query_update_path.arg(table_path, name, path, QString::number(ID));
    QSqlQuery query_a;

    if (query_a.exec(query_update_path)) {
        qDebug() << "PBase::updatePath() update access id " << ID << " from table " + table_path;
        return true;
    }
    else {
        qDebug() << "PBase::updatePath() update FAIL! id " << ID << " from table " + table_path
                 << "\nERROR: " << query_a.lastError().text();
        return false;
    }
}


//===========
//GET param
//===========

int PBase::getUserID(QString name) {

    QString query_get_user_id = "SELECT id, user_name FROM %1 WHERE user_name = '%2';";
    query_get_user_id = query_get_user_id.arg(table_users, name);
    QSqlQuery query_a(query_get_user_id);

    int id = 0;
    while (query_a.next()) {
        id = query_a.value("id").toInt();
        if (query_a.value("user_name").toString() == name)
            break;
    }

    return id;

}

QString PBase::getUserName(int ID) {
    QString query_get_user_name = "SELECT id, user_name FROM %1 WHERE id = %2;";
    query_get_user_name = query_get_user_name.arg(table_users, QString::number(ID));
    QSqlQuery query_a(query_get_user_name);

    QString name = 0;
    while (query_a.next()) {
        name = query_a.value("user_name").toString();
        if (query_a.value("id").toInt() == ID)
            break;
    }
    return name;

}

bool PBase::getUserAccessPath(QString name, int pathID) {

    QString pathIDString = "path" + QString::number(pathID);
    QString query_get_user_access_path = "SELECT user_name, %1 FROM %2 WHERE user_name = '%3';";
    query_get_user_access_path = query_get_user_access_path.arg(pathIDString, table_users, name);
    QSqlQuery query_a(query_get_user_access_path);

    bool access = false;
    while (query_a.next()) {
        access = query_a.value(pathIDString).toBool();
        if (query_a.value("user_name").toString() == name)
            break;
    }

    return access;
}

QString PBase::getPath(int ID) {

        QString query_get_path = "SELECT * FROM %1 WHERE id = %2;";
        query_get_path = query_get_path.arg(table_path, QString::number(ID));
        QSqlQuery query_a(query_get_path);

        QString path = 0;
        while (query_a.next()) {
            path = query_a.value("path").toString();
            if (query_a.value("id").toInt() == ID)
                break;
        }

        return path;
}

QString PBase::getNamePath(int ID) {

        QString query_get_name = "SELECT * FROM %1 WHERE id = %2;";
        query_get_name = query_get_name.arg(table_path, QString::number(ID));
        QSqlQuery query_a(query_get_name);

        QString name = 0;
        while (query_a.next()) {
            name = query_a.value("name").toString();
            if (query_a.value("id").toInt() == ID)
                break;
        }

        return name;
}

int PBase::getCountPath() {


}

//=====debug===

QSqlQueryModel * PBase::getQueryModel(QString table_name, QObject *parent) {
    QSqlQueryModel * model = new QSqlQueryModel(parent);
    QSqlQuery query;
    query.exec("SELECT * FROM " + table_name);
    model->setQuery(query);

    return model;
}

QSqlTableModel * PBase::getTableModel(QString table_name, QObject *parent) {
    QSqlTableModel * model = new QSqlTableModel(parent);
    model->setTable(table_name);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));

    return model;
}
