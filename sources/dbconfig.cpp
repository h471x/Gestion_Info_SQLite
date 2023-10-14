#include "header/dbconfig.h"
#include "header/dbconnect.h"
#include <QCoreApplication>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include "ui_mainwindow.h"
#include <QDialog>

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject(parent){
}

DatabaseManager::~DatabaseManager(){
    if (mydb.isOpen()) {
        mydb.close();
    }
}

void DatabaseManager::initTables(){
    QSqlQuery query;
    //     query.exec("CREATE TABLE IF NOT EXISTS PRODUCT (Id INTEGER PRIMARY KEY AUTOINCREMENT,Name TEXT NOT NULL,Type TEXT NOT NULL,Price REAL NOT NULL,Date DATE NOT NULL,Number INTEGER NOT NULL DEFAULT 0,Threshold INTEGER);");
    //     query.exec("CREATE TABLE IF NOT EXISTS ADMIN (username TEXT NOT NULL, PASSWORD TEXT NOT NULL);");
    query.exec("CREATE TABLE IF NOT EXISTS CATEGORIE (IdCategorie INTEGER NOT NULL ,NomCategorie TEXT NOT NULL ,NbeMateriel INTEGER NOT NULL DEFAULT 0 ,PRIMARY KEY(IdCategorie));");
    query.exec("CREATE TABLE IF NOT EXISTS FOURNISSEUR (NomFournisseur TEXT NOT NULL ,PRIMARY KEY(NomFournisseur));");
    query.exec("CREATE TABLE IF NOT EXISTS ADMIN (UsernameAdmin TEXT NOT NULL UNIQUE ,Password TEXT NOT NULL ,NomAdmin TEXT NOT NULL ,PrenomAdmin TEXT NOT NULL ,TelephoneAdmin TEXT NOT NULL ,AdresseAdmin TEXT NOT NULL ,PRIMARY KEY(UsernameAdmin));");
    query.exec("CREATE TABLE IF NOT EXISTS UTILISATEUR (IdUtilisateur  INTEGER NOT NULL ,NomUtilisateur TEXT NOT NULL ,PrenomUtilisateur TEXT ,AdresseUtilisateur TEXT  NOT NULL ,TelephoneUtilisateur TEXT NOT NULL,PRIMARY KEY(IdUtilisateur));");
    query.exec("CREATE TABLE IF NOT EXISTS MATERIEL (IdMateriel INTEGER NOT NULL, NomMateriel TEXT NOT NULL, Marque TEXT NOT NULL, Etat TEXT NOT NULL, DEnregistrement TEXT NOT NULL, IdCategorie INTEGER NOT NULL, NomFournisseur TEXT, UsernameAdmin TEXT, IdUtilisateur INTEGER, PRIMARY KEY(IdMateriel), FOREIGN KEY(IdCategorie) REFERENCES CATEGORIE(IdCategorie) ON UPDATE CASCADE ON DELETE CASCADE, FOREIGN KEY(NomFournisseur) REFERENCES FOURNISSEUR(NomFournisseur) ON UPDATE SET NULL ON DELETE SET NULL, FOREIGN KEY(UsernameAdmin) REFERENCES ADMIN(UsernameAdmin) ON UPDATE CASCADE ON DELETE SET NULL, FOREIGN KEY(IdUtilisateur) REFERENCES UTILISATEUR(IdUtilisateur) ON UPDATE SET NULL ON DELETE SET NULL);");
}

void DatabaseManager::initValues(){
    QSqlQuery query;
    query.prepare("INSERT INTO ADMIN(UsernameAdmin, Password, NomAdmin, PrenomAdmin, TelephoneAdmin, AdresseAdmin) VALUES(:usernameadmin, :passwordadmin, :nameadmin, :prenom, :phone, :adresse)");
    query.bindValue(":usernameadmin", "admin");
    query.bindValue(":passwordadmin", "admin");
    query.bindValue(":nameadmin", "admin");
    query.bindValue(":prenom", "admin");
    query.bindValue(":phone", "033333333");
    query.bindValue(":adresse", "Fianarantsoa");
    query.exec();

    query.prepare("INSERT INTO CATEGORIE(NomCategorie, NbeMateriel) VALUES(:nom, :nbre)");
    query.bindValue(":nom", "ORDINATEUR");
    query.bindValue(":nbre", 10);
    query.exec();

    for(int i = 0; i < 20; i++){
        query.prepare("INSERT OR IGNORE INTO MATERIEL(IdMateriel, NomMateriel, Marque, Etat, DEnregistrement, IdCategorie) VALUES(:idmat, :nomat, :marque, :etat, :date, :id)");
        query.bindValue(":idmat", i);
        query.bindValue(":nomat", "DELL INSPIRON");
        query.bindValue(":marque", "DELL");
        query.bindValue(":etat", "3");

        // Get the current date
        QDate currentDate = QDate::currentDate();

        query.bindValue(":date", currentDate);
        query.bindValue(":id", i);
        query.exec();
    }

}

void DatabaseManager::createdb(){
    initTables();
    initValues();
}

bool DatabaseManager::initializeDatabase(){
    // Database init
    DatabaseConnection& dbInstance = DatabaseConnection::getInstance();
    QSqlDatabase db = dbInstance.getConnection();
    // here to init the database
    pragma();
    createdb();
    return true;
}

void DatabaseManager::pragma(){
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");

//    if (query.lastError().isValid()) {
//        // Operation failed
//        qDebug() << "Foreign key activation failed:" << query.lastError().text();
//        return false;
//    } else {
//        // Operation succeeded
//        qDebug() << "Foreign keys activated successfully";
//        return true;
//    }
}

void DatabaseManager::toggleBtn(){
//    bool isDark = false;
//    if (isDark) {
//        // Change l'icône du bouton "editBtn" pour la version sombre
//        editBtn->setIcon(QIcon(":/darkicon/icons/dark/edit-2.svg"));

//        // Change le tooltip du bouton "editBtn" pour la version sombre
//        editBtn->setToolTip("Edit (Dark Mode)");
//        isDark = true;
//    }else if(!isDark){

//        isDark = false;
//    }
    return;
}

QSqlTableModel* DatabaseManager::createUserTableModel(QTableWidget* tableWidget){
    QSqlTableModel* model = new QSqlTableModel(tableWidget, mydb);
    model->setTable("MATERIEL");

    // Populate the model with data
    model->select();

    // Set up the columns you want to display manually
    QList<int> selectedColumns = {0, 1, 2, 3, 4}; // Replace with the column indexes you want to display

    // Set up the QTableWidget with the model's data
//    int tableColumnCount = model->columnCount();
    int tableColumnCount = selectedColumns.size();
    tableWidget->setColumnCount(tableColumnCount);
    tableWidget->setAlternatingRowColors(true);

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

//    for (int row = 0; row < tableRowCount; ++row) {
//        for (int column = 0; column < tableColumnCount; ++column) {
//            QModelIndex index = model->index(row, column);
//            QString data = model->data(index).toString();
//            QTableWidgetItem* item = new QTableWidgetItem(data);
//            tableWidget->setItem(row, column, item);
//            if (item) {
//                item->setTextAlignment(Qt::AlignCenter);
//                item->setFont(tableFont);
//            }
//        }
//    }

    // Ajoute une colonne "Actions" au tableau
    tableWidget->setColumnCount(tableColumnCount + 1);
    tableWidget->setHorizontalHeaderItem(tableColumnCount, new QTableWidgetItem("Actions"));

    for (int row = 0; row < tableRowCount; ++row) {
        // Crée les boutons "Add" et "Delete" pour chaque ligne
        QPushButton* editBtn = new QPushButton;
        QPushButton* deleteBtn = new QPushButton;

        // Connexion du signal "clicked" du bouton à une fonction lambda
//         connect(editBtn, &QPushButton::clicked, [row]() {
//               // Afficher le numéro de ligne
//               qDebug() << "Clicked on row" << row+1;
//         });

        connect(editBtn, &QPushButton::clicked, this, [tableWidget, row]() {
            // Accéder aux données de la ligne
            QString id = tableWidget->item(row, 0)->data(Qt::DisplayRole).toString();
            QString nom = tableWidget->item(row, 1)->data(Qt::DisplayRole).toString();
            // Afficher les données dans QDebug
            qDebug() << "Data of row" << row+1 << ": Id=" << id << " , NomMateriel=" << nom;
        });

        // Définit les tooltips
        editBtn->setToolTip("Edit");
        deleteBtn->setToolTip("Delete");

        // Définit le style du tooltip
        editBtn->setStyleSheet("QToolTip{background-color: #eaeff5;}");
        deleteBtn->setStyleSheet("QToolTip{background-color: #eaeff5;}");

//        // Vérifie la valeur actuelle de isDark
//        if(isDark){
//            // Change l'icône du bouton "editBtn" pour la version sombre
//            editBtn->setIcon(QIcon(":/darkicon/icons/dark/edit-2.svg"));

//            // Change le tooltip du bouton "editBtn" pour la version sombre
//            editBtn->setToolTip("Edit (Dark Mode)");
//        } else {
//            // Change l'icône du bouton "editBtn" pour la version claire
//            editBtn->setIcon(QIcon(":/lighticon/icons/light/edit-2.svg"));

//            // Change le tooltip du bouton "editBtn" pour la version claire
//            editBtn->setToolTip("Edit");
//        }

        // Charge l'icône à partir du fichier resources.qrc
        editBtn->setIcon(QIcon(":/darkicon/icons/dark/edit-2.svg"));
        // Définit la taille de l'icône si nécessaire
        editBtn->setIconSize(QSize(30, 30));

        // Charge l'icône à partir du fichier resources.qrc
        deleteBtn->setIcon(QIcon(":/darkicon/icons/dark/trash.448x512.png"));
        // Définit la taille de l'icône si nécessaire
        deleteBtn->setIconSize(QSize(30, 30));

        editBtn->setFocusPolicy(Qt::NoFocus);
        deleteBtn->setFocusPolicy(Qt::NoFocus);

        // Crée un layout horizontal pour les boutons
        QHBoxLayout* actionsLayout = new QHBoxLayout;
        actionsLayout->addWidget(editBtn);
        actionsLayout->addWidget(deleteBtn);

        // Crée un widget pour contenir le layout
        QWidget* actionsWidget = new QWidget;
        actionsWidget->setLayout(actionsLayout);

        // Ajoute le widget au tableau
        tableWidget->setCellWidget(row, tableColumnCount, actionsWidget);

        // Utilise setItem pour le deuxième bouton "Delete"
        QTableWidgetItem* deleteItem = new QTableWidgetItem("Delete");
        tableWidget->setItem(row, tableColumnCount, deleteItem);

        // Personnalise les boutons si besoin
        // ...

        // Tu peux ajouter des slots (fonctions) aux boutons plus tard si tu souhaites
        // ...

        tableWidget->setRowHeight(row, 60);
    }

    for (int column = 0; column < tableColumnCount; ++column) {
        int selectedColumn = selectedColumns[column];
        QTableWidgetItem* headerItem = new QTableWidgetItem(model->headerData(selectedColumn, Qt::Horizontal).toString());
        tableWidget->setHorizontalHeaderItem(column, headerItem);

        for (int row = 0; row < tableRowCount; ++row) {
            QModelIndex index = model->index(row, selectedColumn);
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
