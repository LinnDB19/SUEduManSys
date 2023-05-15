#include "theDB.h"
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>

theDB* theDB::_instance = nullptr;

theDB* theDB::instance()
{
    if(_instance == nullptr) _instance = new theDB;
    return _instance;
}

theDB::theDB()
{
    db.setDatabaseName(DBName);
    if(!db.open())
    {
        QMessageBox::warning(0, QString("CONNECT ERROR"), db.lastError().text());
        return;
    }

    //指令绑定数据库
    query = QSqlQuery(db);

    //如果没有学生表，就创建
    if(!existTable("studentTable")) createStudentTable();
    //如果没有考试表，就创建
}


bool theDB::existTable(const QString& qstr)
{
    if(db.tables().contains(qstr)) return true;
    else return false;
}

bool theDB::createStudentTable()
{
    QString sqlstr = "CREATE TABLE studentTable ("
            "id INTERGER PRIMARY KEY, "
            "name VARCHAR(40) NOT NULL, "
            "gender VARCHAR(4) NOT NULL, "
            "age INTERGER NOT NULL, "
            "native VARCHAR(40),"
            "photo BLOB,"
            "memo MEMO);";
    toQuery(sqlstr);

    return true;
}

bool theDB::toQuery(const QString& qstr)
{
    if(!query.exec(qstr))
    {
        QMessageBox::warning(0, QString("query ERROR"), query.lastError().text());
        return false;
    }
    return true;
}

bool theDB::toQuery()
{
    if(!query.exec())
    {
        QMessageBox::warning(0, QString("query ERROR"), query.lastError().text());
        return false;
    }
    return true;
}

bool theDB::insertToStudentTable(const STUTABELROW& values)
{
    //构造 INSERT INTO TABLE_NAME VALUES (value1,value2,value3,...valueN);

    QString sqlstr("INSERT INTO studentTable "
                   "VALUES(:id, :name, :gender, :age, :NativePlace, :photo, :memo);");

    query.prepare(sqlstr);
    query.bindValue(":id", values.id);
    query.bindValue(":name", values.name);
    query.bindValue(":gender", values.genger);
    query.bindValue(":age", values.age);
    query.bindValue(":NativePlace", values.NativePlace);
    query.bindValue(":photo", values.photo);
    query.bindValue(":memo", values.memo);

    return toQuery();
}
