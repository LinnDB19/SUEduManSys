/* 这个程序只会连接一个数据库，设计成singleton*/
#ifndef THEDB_H
#define THEDB_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

struct STUTABELROW
{
    int id;
    QString name;
    QString genger;
    int age;
    QString NativePlace;
    QByteArray photo;
    QString memo;
};

class theDB
{
private:
    static theDB* _instance;
    //私有数据
    QString DBName = "DataBase.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query;

private:
    //私有工具成员函数
    bool existTable(const QString& qstr);
    bool createStudentTable();
    bool toQuery(const QString& qstr);
    bool toQuery();

protected:
    theDB();

public:
    static theDB* instance();

    QSqlDatabase* getDataBase() {return &db;}
    bool insertToStudentTable(const STUTABELROW& values);
    ~theDB() {}
};

#endif // THEDB_H
