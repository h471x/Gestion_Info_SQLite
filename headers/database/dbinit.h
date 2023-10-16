#ifndef DBINIT_H
#define DBINIT_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QCoreApplication>
#include <QDate>
#include <QString>

class DbInit
{
public: //Constructor
    DbInit();

public: //Method
    void initdb();
    void closeConnection();

public: //Object Instance
    QSqlDatabase mydb;

public: //Conflict handler
    static DbInit& getInstance();
    QSqlDatabase getConnection();   
};

#endif // DBINIT_H
