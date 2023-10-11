// databaseconnection.h

#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QSqlDatabase>

class DatabaseConnection
{
public:
    static DatabaseConnection& getInstance();
    QSqlDatabase getConnection();

private:
    DatabaseConnection();
    QSqlDatabase mydb;
};

#endif // DBCONNECT_H
