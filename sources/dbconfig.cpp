#include "header/dbconfig.h"
#include "header/dbconnect.h"
#include <QCoreApplication>
#include <QHeaderView>
#include <QTableWidgetItem>

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject(parent){
}

DatabaseManager::~DatabaseManager(){
    if (mydb.isOpen()) {
        mydb.close();
    }
}

void DatabaseManager::createdb(){
    QSqlQuery query;
     query.exec("CREATE TABLE IF NOT EXISTS PRODUCT (Id INTEGER PRIMARY KEY AUTOINCREMENT,Name TEXT NOT NULL,Type TEXT NOT NULL,Price REAL NOT NULL,Date DATE NOT NULL,Number INTEGER NOT NULL DEFAULT 0,Threshold INTEGER);");
     query.exec("CREATE TABLE IF NOT EXISTS ADMIN (username TEXT NOT NULL, PASSWORD TEXT NOT NULL);");
}

bool DatabaseManager::initializeDatabase(){
    // Database init
    DatabaseConnection& dbInstance = DatabaseConnection::getInstance();
    QSqlDatabase db = dbInstance.getConnection();
    // here to init the database
    // createdb();
    return true;
}

QSqlTableModel* DatabaseManager::createUserTableModel(QTableWidget* tableWidget)
{
    QSqlTableModel* model = new QSqlTableModel(tableWidget, mydb);
    model->setTable("PRODUCT");

    // Populate the model with data
    model->select();

    // Set up the QTableWidget with the model's data
    int tableColumnCount = model->columnCount();
    tableWidget->setColumnCount(tableColumnCount);

    for (int column = 0; column < tableColumnCount; ++column) {
        QTableWidgetItem* headerItem = new QTableWidgetItem(model->headerData(column, Qt::Horizontal).toString());
        tableWidget->setHorizontalHeaderItem(column, headerItem);
    }

    int tableRowCount = model->rowCount();
    tableWidget->setRowCount(tableRowCount);

    QFont tableFont;
    tableFont.setPointSize(11);

    tableWidget->horizontalHeader()->setFont(tableFont);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setMouseTracking(true);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for (int row = 0; row < tableRowCount; ++row) {
        for (int column = 0; column < tableColumnCount; ++column) {
            QModelIndex index = model->index(row, column);
            QString data = model->data(index).toString();
            QTableWidgetItem* item = new QTableWidgetItem(data);
            tableWidget->setItem(row, column, item);
            if (item) {
                item->setTextAlignment(Qt::AlignCenter);
                item->setFont(tableFont);
            }
        }
    }

    return model;
}
