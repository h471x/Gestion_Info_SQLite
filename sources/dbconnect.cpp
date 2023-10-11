#include "header/dbconnect.h"
#include <QCoreApplication>

DatabaseConnection::DatabaseConnection()
{
    // Get the directory of the application executable
    QString appDirPath = QCoreApplication::applicationDirPath();

    // Append the relative path to the database file
    QString dbFilePath = appDirPath + "/database.db";

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(dbFilePath);

    if (!mydb.open()) {
        return;
    }
}

DatabaseConnection& DatabaseConnection::getInstance()
{
    static DatabaseConnection instance;
    return instance;
}

QSqlDatabase DatabaseConnection::getConnection()
{
    return mydb;
}
