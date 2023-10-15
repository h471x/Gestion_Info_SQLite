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
    DatabaseManager(Ui::MainWindow* ui);

public slots:
    void changeIcon();

public:
    explicit DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager();

    bool initializeDatabase();
    void pragma();
    void initTables();
    void initValues();
    void createdb();
    void toggleBtn();

    QSqlTableModel* createUserTableModel(QTableWidget* tableWidget);

private:
    Ui::MainWindow* ui;
    bool isDarkIcon;

private:
    QSqlDatabase mydb;

private:
    QPushButton* editBtn;
    QPushButton* deleteBtn;
};

#endif // DBCONFIG_H
