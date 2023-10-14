#ifndef DBCONFIG_H
#define DBCONFIG_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableWidget>
#include "mainwindow.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager();

    bool initializeDatabase();
    void pragma();
    void initTables();
    void initValues();
    void createdb();
    QSqlTableModel* createUserTableModel(QTableWidget* tableWidget);

private:
    QSqlDatabase mydb;
};

#endif // DBCONFIG_H
